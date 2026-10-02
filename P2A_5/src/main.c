#include "riscv_types.h"
#include "riscv_uart.h"
#include "log.h"

int main() {
    uint8_t tc_header[5];
    uint16_t packet_id, packet_control;
    uint8_t version, type, sec_hdr_flag;
    uint16_t apid;
    uint8_t seq_flags;
    uint16_t packet_seq, pkt_data_len;
    int32_t rec;

    // Habilitar transmisión y recepción
    riscv_uart_enable_TX();
    riscv_uart_enable_RX();

    while (1) {
        // 1. El inicio del TC siempre es 0x1B. Ignorar todo byte previo diferente de 0x1B.
        do {
            do {
                rec = riscv_getchar();
            } while (rec == -1);
        } while ((uint8_t)rec != 0x1B);

        // 2. Una vez leído 0x1B, esperar y guardar los siguientes 5 bytes
        for (int i = 0; i < 5; i++) {
            do {
                rec = riscv_getchar();
            } while (rec == -1);
            tc_header[i] = (uint8_t)rec;
        }

        // 3. Decodificar la cabecera del paquete (Campos del TC)
        // reconstruir Packet ID (2 bytes: 0x1B y tc_header[0])
        packet_id = (0x1B << 8) | tc_header[0];
        version = (packet_id >> 13) & 0x07;
        type = (packet_id >> 12) & 0x01;
        sec_hdr_flag = (packet_id >> 11) & 0x01;
        apid = packet_id & 0x07FF;

        // reconstruir Packet Sequence Control (2 bytes: tc_header[1] y tc_header[2])
        packet_control = (tc_header[1] << 8) | tc_header[2];
        seq_flags = (packet_control >> 14) & 0x03;
        packet_seq = packet_control & 0x3FFF;

        // Packet Data Length (2 bytes: tc_header[3] y tc_header[4])
        pkt_data_len = (tc_header[3] << 8) | tc_header[4];

        // Imprimir los valores decodificados
        printf("PACKET PRIMARY HEADER ... 1B %02X %02X %02X %02X %02X\n",
               tc_header[0], tc_header[1], tc_header[2], tc_header[3], tc_header[4]);
        printf("VERSION: %d\n", version);
        printf("TYPE: %d (%s)\n", type, type ? "TC" : "TM");
        printf("PKT SEC HDR FLAG: %d (%s)\n", sec_hdr_flag, sec_hdr_flag ? "YES" : "NO");
        printf("APID: %d (0x%X)\n", apid, apid);
        printf("SEQUENCE FLAGS: %d\n", seq_flags);
        printf("PACKET SEQUENCE: %d (0x%X)\n", packet_seq, packet_seq);
        printf("PKT DATA LEN: %d (%d bytes - 1)\n\n", pkt_data_len, pkt_data_len + 1);

        // 4. Enviar un ACK de confirmación ("OK") por la UART
        riscv_print_string("OK\n");
    }

    return 0;
}
