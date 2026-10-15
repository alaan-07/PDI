#include "riscv_types.h"
#include "riscv_uart.h"
#include "dispatch.h"
#include "log.h"

#define TC_START_BYTE 0x1B

uint8_t tc_header[5];
volatile int state = 0; // 0: Esperando 0x1B, 1 a 5: Leyendo los 5 bytes de la cabecera
volatile uint32_t flag = 0;

// UART ISR handler guiado por interrupciones
void uart_rx_irq_handler(void) {
    int32_t rec = riscv_getchar();
    if (rec == -1) return;
    uint8_t byte_recibido = (uint8_t)rec;

    if (state == 0) {
        // 1. El inicio del TC siempre es 0x1B. Ignorar todo lo anterior.
        if (byte_recibido == TC_START_BYTE) {
            state = 1; // Pasamos a leer los 5 bytes siguientes
        }
    } else {
        // 2 y 3. Guardar los siguientes 5 bytes en el array
        tc_header[state - 1] = byte_recibido;
        state++;

        if (state > 5) {
            // 4. Cabecera completa, avisamos al main mediante el flag
            flag = 1;
            state = 0; // Reiniciamos estado para el siguiente telecomando
        }
    }
}

int main() {
    uint16_t packet_id, packet_control;
    uint8_t version, type, sec_hdr_flag;
    uint16_t apid;
    uint8_t seq_flags;
    uint16_t packet_seq, pkt_data_len;

    // Habilitar TX y RX en la UART
    riscv_uart_enable_TX();
    riscv_uart_enable_RX();

    // Configurar e instalar el manejador de interrupciones
    install_irq_handler(UART_IRQ, uart_rx_irq_handler);
    riscv_uart_enable_RI();
    plic_irq_unmask(UART_IRQ);
    enable_ext_irq();
    enable_irq();

    riscv_print_string("Iniciando decodificador de Telecomando por IRQ...\n");

    while (1) {
        // 5. El main espera en bucle hasta que el flag se active por la ISR
        while (!flag) {
            // Espera activa o inactiva hasta recibir el paquete completo
        }

        // 6. Limpiar el flag y decodificar el paquete
        flag = 0;

        packet_id = (TC_START_BYTE << 8) | tc_header[0];
        version = (packet_id >> 13) & 0x07;
        type = (packet_id >> 12) & 0x01;
        sec_hdr_flag = (packet_id >> 11) & 0x01;
        apid = packet_id & 0x07FF;

        packet_control = (tc_header[1] << 8) | tc_header[2];
        seq_flags = (packet_control >> 14) & 0x03;
        packet_seq = packet_control & 0x3FFF;

        pkt_data_len = (tc_header[3] << 8) | tc_header[4];

        // Imprimir los campos decodificados en la consola de Eclipse
        printf("PACKET PRIMARY HEADER ... 1B %02X %02X %02X %02X %02X\n",
               tc_header[0], tc_header[1], tc_header[2], tc_header[3], tc_header[4]);
        printf("VERSION: %d\n", version);
        printf("TYPE: %d (%s)\n", type, type ? "TC" : "TM");
        printf("PKT SEC HDR FLAG: %d (%s)\n", sec_hdr_flag, sec_hdr_flag ? "YES" : "NO");
        printf("APID: %d (0x%X)\n", apid, apid);
        printf("SEQUENCE FLAGS: %d\n", seq_flags);
        printf("PACKET SEQUENCE: %d (0x%X)\n", packet_seq, packet_seq);
        printf("PKT DATA LEN: %d (%d bytes - 1)\n\n", pkt_data_len, pkt_data_len);

        // 7. Enviar un ACK de confirmación ("OK") por la UART de vuelta
        riscv_print_string("OK\n");

        // 8. Vuelve arriba a esperar el siguiente TC
    }

    return 0;
}
