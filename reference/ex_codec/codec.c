/*
 * Advanced ICS Lab. Networking
 *
 * Kazuya Sakai, Tokyo Metropolitan University.
 * Feb. 3rd, 2015.
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_LEN 16

/*
 * Memo:
 * uint8_t is defined in stdint.h
 */

/*
 * 1-byte    16-byte       4-byte
 * -----------------------------------
 * | cmd |  file_name  |  file_size  |
 * -----------------------------------
 * 0    0 1          16 17         20
 * Offset (bytes)
 */

/*
 * Encoding
 */

// This function encodes an 8-bit unsigned integer into a byte.
int encode_uint8(uint8_t *bytes, uint8_t cmd, int offset) {
  bytes[offset++] = cmd;
  return offset;
}

// This function encodes a string into a bytecode by big-endian.
int encode_str(uint8_t *bytes, char *var, int offset, int size) {
  int i;
  
  for (i = 0; i < size; i++) {
    bytes[offset++] = (uint8_t)var[i];
  }
  
  return offset;
}

// This function encodes a 4-byte integer into a bytecode by big-endian.
int encode_int(uint8_t *bytes, int var, int offset, int size) {
  int i;
  for (i = 0; i < size; i++) {
    bytes[offset++] = (uint8_t)(var >> ((size - 1) - i) * 8);
  }
  
  return offset;
}

// This function encodes a packet into a bytecode.
int encode_pkt(uint8_t *bytes, uint8_t cmd, char file_name[FILE_NAME_LEN], int file_size) {
  int offset;
  
  offset = encode_uint8(bytes, cmd, 0);
  offset = encode_str(bytes, file_name, offset, FILE_NAME_LEN);
  offset = encode_int(bytes, file_size, offset, sizeof(file_size));
  
  return offset;
}

/*
 * Decoding
 */

// This function decodes a byte to an 8-bit integer.
int decode_uint8(uint8_t *bytes, uint8_t *var, int offset) {
  *var = bytes[offset++];
  
  return offset;
}

// This function decodes a bytecode to a string.
int decode_str(uint8_t *bytes, char *file_name, int offset, int size) {
  int i;
  for (int i = 0; i < size; i++) file_name[i] = bytes[offset++];
  
  return offset;
}

// This function decodes a bytecode to a 4-byte integer.
int decode_int(uint8_t *bytes, int *file_size, int offset, int size) {
  int i;
  for (int i = 0; i < size; i++) *file_size += bytes[offset++] << ((size - 1) - i) * 8;
  
  return offset;
}

// This functin decodes a bytecode to a packet.
int decode_pkt(uint8_t *bytes, uint8_t *cmd, char *file_name, int *file_size) {
  int offset = 0;
  
  offset = decode_uint8(bytes, cmd, offset);
  offset = decode_str(bytes, file_name, offset, FILE_NAME_LEN);
  offset = decode_int(bytes, file_size, offset, sizeof(int));
  
  return offset;
}

void main () {
  int i;
  
  // The input variables to an encoder
  uint8_t cmd = 0x1;
  char file_name[FILE_NAME_LEN] = "filename.txt";
  int file_size = 5342;
  
  // The output variables from a decoder.
  uint8_t decoded_cmd;
  char decoded_file_name[FILE_NAME_LEN];
  int decoded_file_size;
  
  // encoded data
	char bytes[21];
  int offset = 0;
  
  // The packet to be encoded.
  printf("pkt = [%x, %s, %d]\n", cmd, file_name, file_size);

  // encoding
  encode_pkt(bytes, cmd, file_name, file_size);
  
  // print the bytes code.
  printf("E(pkt) =");
  for (i = 0; i < 21; i++) printf(" %x", bytes[i]);
  printf("\n");
  
  // decoding
  decode_pkt(bytes, &decoded_cmd, decoded_file_name, &decoded_file_size);
  
  // print a decoded packet.
  printf("[%d, %s, %d] is decoded\n", decoded_cmd, decoded_file_name, decoded_file_size);
  
}