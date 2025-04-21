#include <stdio.h>
#include <string.h>

#define POLYNOMIAL 0x1021
#define WIDTH (8 * sizeof(unsigned short))
#define TOPBIT (1 << (WIDTH - 1))

unsigned short crc16(const char *data, size_t length) {
    unsigned short remainder = 0;
    size_t byte;
    int bit;

    for (byte = 0; byte < length; ++byte) {
        remainder ^= (unsigned short)(data[byte] << (WIDTH - 8));
        for (bit = 0; bit < 8; ++bit) {
            if (remainder & TOPBIT) {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            } else {
                remainder = (remainder << 1);
            }
        }
    }
    return remainder;
}

unsigned char checksum(const char *data, size_t length) {
    unsigned char sum = 0;
    size_t i;
    for (i = 0; i < length; ++i) {
        sum += data[i];
    }
    return ~sum;
}

int parity_check(const char *data, size_t length) {
    int parity = 0;
    size_t i;
    for (i = 0; i < length; ++i) {
        parity ^= data[i];
    }
    return parity % 2;
}

void hamming_code(const char *data) {
    printf("Hamming code generation is not implemented yet.\n");
}

void sender(const char *message, int choice) {
    printf("\nSender Side:\n");
    switch (choice) {
        case 1:
            printf("CRC-16: %04X\n", crc16(message, strlen(message)));
            break;
        case 2:
            printf("Checksum: %02X\n", checksum(message, strlen(message)));
            break;
        case 3:
            printf("Parity: %s\n", (parity_check(message, strlen(message)) == 0) ? "Even" : "Odd");
            break;
        case 4:
            hamming_code(message);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void receiver(const char *message, int choice) {
    printf("\nReceiver Side:\n");
    switch (choice) {
        case 1:
            printf("CRC-16: %04X\n", crc16(message, strlen(message)));
            break;
        case 2:
            printf("Checksum: %02X\n", checksum(message, strlen(message)));
            break;
        case 3:
            printf("Parity: %s\n", (parity_check(message, strlen(message)) == 0) ? "Even" : "Odd");
            break;
        case 4:
            hamming_code(message);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

int main() {
    char message[256];
    int choice;
    
    do {
        printf("\nEnter the message: ");
        fflush(stdin);  // Clear buffer before input
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0; // Remove trailing newline

        printf("\nSelect the error detection technique:\n");
        printf("1. CRC\n");
        printf("2. Checksum\n");
        printf("3. Parity Check\n");
        printf("4. Hamming Code\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear input buffer

        sender(message, choice);
        
        printf("\nDebug: Calling receiver function...\n"); // Debugging
        receiver(message, choice);

        printf("\nDo you want to try another technique? (1 for Yes / 0 for No): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            return 1;
        }
        while (getchar() != '\n'); // Properly clear input buffer

    } while (choice == 1);

    return 0;
}


