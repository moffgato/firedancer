#include "fd_compute_budget_program.h"

/* 700k CU, 0 extra fee (deprecated) */
unsigned char txn1[1191] = {
0x01,0xfd,0x9b,0xec,0x91,0x1b,0x63,0x54,0x7e,0x72,0x48,0xd2,0x0e,0x87,0x76,0x39,
0xc3,0x0b,0xdf,0xb3,0x0a,0x11,0x55,0x58,0xee,0x6a,0x18,0x1c,0x9e,0xa5,0x50,0x17,
0x6e,0x7f,0xec,0xf6,0xa2,0x95,0x7b,0x52,0x47,0x0a,0x78,0xc0,0xe9,0xfc,0x53,0x97,
0xb7,0xfc,0x46,0xcf,0x46,0x19,0x72,0xa8,0x07,0xb6,0x48,0xa3,0x0a,0x88,0x06,0xa1,
0x07,0x01,0x00,0x1b,0x1d,0x11,0x64,0x91,0xfb,0x15,0x92,0x23,0xf0,0xec,0xab,0xaa,
0x10,0xc1,0x3a,0x2b,0x59,0x7c,0x81,0x1e,0xe0,0x01,0x34,0x2d,0x3f,0x78,0x55,0x41,
0xec,0xb4,0x3d,0x0f,0x81,0x55,0x6b,0xb3,0xaf,0x23,0xd8,0x79,0xc5,0x8f,0x44,0x83,
0x89,0x27,0x2e,0x84,0xe8,0x9e,0xab,0xb0,0x54,0x74,0x8a,0xb9,0x54,0x58,0x2f,0x92,
0xca,0x03,0xd7,0x0d,0xf9,0x59,0x66,0x8c,0x25,0x62,0x37,0x28,0x19,0x7b,0x24,0x1f,
0x8d,0x9f,0x88,0x8e,0xbe,0x56,0xda,0xa9,0x03,0x6e,0x43,0x1e,0x97,0x83,0xbc,0x89,
0x49,0x1d,0x43,0xb7,0x8d,0x08,0x41,0x3a,0xa6,0x21,0x31,0x0c,0x1f,0x15,0xb3,0x53,
0x5b,0x3f,0x3d,0x6c,0xd3,0x4e,0x1e,0xd7,0x46,0x7c,0xf1,0xe8,0x0f,0xf8,0x03,0x51,
0x02,0x64,0x88,0x84,0xfe,0x15,0xad,0xd9,0x50,0x22,0xae,0x13,0x56,0x3a,0x11,0x99,
0x2e,0x72,0x7c,0x91,0xbd,0xb6,0xb5,0x5b,0xc1,0x83,0xd9,0xd7,0x47,0x43,0x6c,0x80,
0xa4,0x83,0xd8,0xc8,0x64,0x93,0xda,0x33,0x52,0xf9,0xf1,0xd1,0x05,0xfd,0xfe,0x49,
0x71,0xcf,0xa8,0x0e,0x9d,0xd7,0x77,0xbf,0xc5,0xd0,0xf6,0x83,0xeb,0xb6,0xe1,0x29,
0x4b,0x92,0x13,0x7b,0xb7,0xe6,0x2d,0xf6,0xc8,0xb4,0xa8,0x5f,0xe1,0xa6,0x7d,0xb4,
0x4d,0xc1,0x2d,0xe5,0xdb,0x33,0x0f,0x7a,0xc6,0x6b,0x72,0xdc,0x65,0x8a,0xfe,0xdf,
0x0f,0x4a,0x41,0x5b,0x43,0xff,0x61,0x49,0x1a,0x93,0x11,0x12,0xdd,0xf1,0xbd,0x81,
0x47,0xcd,0x1b,0x64,0x13,0x75,0xf7,0x9f,0x58,0x25,0x12,0x6d,0x66,0x54,0x80,0x87,
0x46,0x34,0xfd,0x0a,0xce,0xba,0xa2,0x84,0xea,0xf2,0x3e,0xdf,0x97,0x5b,0x37,0x1b,
0xa2,0x81,0x87,0x72,0xf9,0x3d,0xba,0xe7,0x28,0x36,0xbb,0xde,0xa2,0x8b,0x07,0xd4,
0x0f,0x3c,0xf8,0xb4,0x85,0xc4,0x15,0xde,0x8d,0x2e,0xba,0x7d,0xb2,0x16,0x52,0x7d,
0xff,0x4b,0x60,0xe8,0xf3,0xa5,0x31,0x1c,0x74,0x0d,0xad,0xb2,0x33,0xe1,0x3e,0x12,
0x54,0x7e,0x22,0x67,0x50,0xef,0x0d,0x8b,0x6f,0xda,0x2c,0xeb,0xa4,0x1d,0xa1,0x5d,
0x40,0x95,0xd1,0xda,0x39,0x2a,0x0d,0x2f,0x8e,0xd0,0xc6,0xc7,0xbc,0x0f,0x4c,0xfa,
0xc8,0xc2,0x80,0xb5,0x6d,0x23,0x24,0x5b,0xb7,0x42,0x54,0xe6,0x5a,0x98,0xcc,0x3f,
0xf4,0xa3,0x74,0x43,0xd7,0x9f,0x52,0x7e,0x44,0xe4,0x49,0x75,0x0a,0xd3,0x04,0x53,
0x8b,0x00,0x6f,0x21,0xbc,0x72,0xd6,0xe8,0xcd,0xf5,0xc7,0x4b,0x97,0x97,0x50,0xd6,
0x0d,0xf1,0x1b,0x4c,0x14,0xae,0x06,0x19,0xad,0x14,0xc1,0x84,0x07,0xc1,0xe6,0xec,
0x60,0xf9,0x39,0x6e,0x96,0xea,0xa0,0x20,0xc6,0x1c,0xc4,0x79,0x71,0x28,0x13,0x46,
0x1c,0xe1,0x53,0x89,0x4a,0x96,0xa6,0xc0,0x0b,0x21,0xed,0x0c,0xfc,0x27,0x98,0xd1,
0xf9,0xa9,0xe9,0xc9,0x4a,0x2b,0x89,0xb9,0xdc,0x8f,0xdf,0x9f,0x34,0x70,0x9a,0x5b,
0x10,0x6b,0x47,0x2f,0x0f,0x39,0xbb,0x6c,0xa9,0xce,0x04,0xb0,0xfd,0x7f,0x2e,0x97,
0x16,0x88,0xe2,0xe5,0x3b,0xef,0x94,0xac,0xc2,0xfb,0x09,0xeb,0x97,0x6c,0x6e,0xb3,
0x00,0x0b,0xab,0x89,0x8c,0xab,0x89,0x1d,0x5b,0x80,0x07,0x02,0xcd,0x1d,0xc8,0x8e,
0x61,0xd7,0xc3,0xc5,0xe6,0xc2,0x28,0x9a,0x6a,0x43,0xd2,0xce,0x91,0xc6,0xf5,0x5c,
0xae,0xc3,0x70,0xf4,0xac,0xc3,0x8a,0x2e,0xd4,0x77,0xf5,0x88,0x13,0x33,0x4c,0x6d,
0x03,0x74,0x9f,0xf2,0xa4,0xcd,0x98,0xf5,0xb4,0x00,0x2c,0x7a,0xf3,0xa4,0x90,0x12,
0x63,0xab,0x55,0xa0,0x3a,0x3f,0x2b,0xd6,0xb0,0xf1,0x8c,0x77,0x8e,0x9f,0xc3,0xe9,
0x5b,0x82,0x1a,0x35,0xa8,0x6c,0x84,0x3e,0x63,0x3a,0xf9,0xfb,0xde,0x7b,0x4e,0x0e,
0x41,0x62,0x16,0x9b,0xb0,0x96,0x00,0x36,0x38,0x4a,0xd6,0xaa,0x55,0x0d,0x5e,0xab,
0x72,0xf4,0xe0,0xba,0x98,0x4d,0x5b,0x7d,0x27,0xf0,0x0d,0x40,0x0e,0x69,0x00,0x69,
0xf1,0xbc,0xca,0xc2,0x81,0xe1,0xec,0xe5,0x98,0xd4,0xcc,0x76,0x21,0x70,0xd8,0xde,
0x86,0xc3,0xbb,0x41,0xde,0x8a,0x21,0x64,0x5b,0x4d,0xf4,0xd3,0x83,0x3e,0x4e,0x64,
0x54,0x01,0x69,0xe2,0x5d,0x8e,0x69,0xb0,0x70,0xd2,0xe5,0xfd,0x60,0x61,0x49,0xc3,
0x9b,0xb0,0xc8,0xa5,0x1f,0xdd,0x94,0x34,0xf0,0x8c,0x12,0xc3,0x5a,0xe2,0x52,0x1a,
0x55,0xc7,0x64,0x08,0x57,0x0f,0x9a,0xb2,0x40,0x4b,0x15,0x0b,0x06,0x6f,0x2b,0x4f,
0x04,0xf3,0x9a,0x72,0xf1,0xb6,0x15,0x0c,0xb2,0x54,0x90,0x99,0xa7,0xe3,0x3a,0x7b,
0x7b,0xf9,0xf4,0x96,0x40,0xa8,0xc4,0x13,0x82,0xf8,0x4c,0x9e,0x20,0xac,0x25,0x15,
0xf6,0x5d,0x56,0xe2,0x16,0x83,0xc8,0x73,0x5f,0xe1,0xa4,0xaa,0xe1,0xf6,0x3f,0x30,
0xd6,0xcf,0x16,0x53,0xe9,0x6b,0xc5,0x9f,0xa0,0xfc,0x6d,0xc2,0x61,0x5c,0x1f,0x4c,
0xe7,0xc0,0xb6,0x3a,0x92,0xa3,0xc6,0x35,0x9e,0x19,0x41,0x3d,0xfa,0xdb,0x16,0xc7,
0xe7,0x1c,0x83,0xe1,0x12,0x68,0x37,0x66,0xcd,0xd4,0x22,0xe9,0x8b,0xc7,0x16,0xb5,
0x3a,0x88,0xe2,0xa5,0x68,0x62,0xc6,0x56,0x91,0x12,0x46,0x76,0xdc,0xf5,0x58,0xe8,
0x8a,0xce,0xbe,0x36,0x24,0xa0,0xe7,0x59,0x09,0x16,0xd7,0x15,0x58,0x51,0x0b,0xe8,
0x78,0xaf,0xed,0xf1,0x46,0xd7,0xf4,0xe8,0xf8,0x07,0x95,0xc5,0x4a,0x3f,0x0f,0xc3,
0xc6,0x9b,0x3e,0xf7,0x42,0x20,0xa4,0x31,0xe3,0x41,0xd0,0x3b,0x33,0x21,0x2e,0x55,
0xda,0xf0,0x08,0x6a,0xbc,0x03,0x06,0x46,0x6f,0xe5,0x21,0x17,0x32,0xff,0xec,0xad,
0xba,0x72,0xc3,0x9b,0xe7,0xbc,0x8c,0xe5,0xbb,0xc5,0xf7,0x12,0x6b,0x2c,0x43,0x9b,
0x3a,0x40,0x00,0x00,0x00,0x08,0x66,0x9c,0x91,0x98,0x54,0x4c,0x1f,0x62,0xdb,0xb6,
0x4e,0xe6,0x68,0x77,0xce,0x58,0x43,0xc7,0x44,0xb7,0x57,0x5d,0xa0,0xbd,0x7b,0x91,
0x62,0x52,0x3f,0x63,0xbd,0xa5,0xa3,0x89,0xe0,0x87,0x4c,0xae,0x89,0xf3,0xac,0xf9,
0xa7,0x4a,0xb7,0x90,0x5c,0x64,0xc5,0x3a,0xdd,0x7a,0x80,0x90,0x9c,0x10,0xac,0xdc,
0xe6,0x2d,0xc1,0x13,0x5a,0x02,0x1b,0x00,0x09,0x00,0x60,0xae,0x0a,0x00,0x00,0x00,
0x00,0x00,0x1c,0x1c,0x00,0x02,0x01,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,
0x0c,0x0d,0x0e,0x0f,0x10,0x07,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,
0x76,0xf1,0xdc,0x83,0x57,0xf5,0x92,0xc9,0x83,0x0e,0x00,0x00,0x00,0x03,0x00,0x00,
0x00,0x41,0x50,0x45,0x04,0x00,0x00,0x00,0x41,0x56,0x41,0x58,0x03,0x00,0x00,0x00,
0x42,0x54,0x43,0x03,0x00,0x00,0x00,0x45,0x54,0x48,0x03,0x00,0x00,0x00,0x47,0x4d,
0x54,0x04,0x00,0x00,0x00,0x4e,0x45,0x41,0x52,0x03,0x00,0x00,0x00,0x53,0x4f,0x4c,
0x03,0x00,0x00,0x00,0x53,0x52,0x4d,0x03,0x00,0x00,0x00,0x53,0x59,0x4e,0x04,0x00,
0x00,0x00,0x55,0x53,0x44,0x43,0x04,0x00,0x00,0x00,0x55,0x53,0x44,0x54,0x03,0x00,
0x00,0x00,0x55,0x53,0x54,0x04,0x00,0x00,0x00,0x6d,0x53,0x4f,0x4c,0x05,0x00,0x00,
0x00,0x77,0x65,0x45,0x54,0x48,0x00};

/* 500k CU, 15001 ulamports per CU; total fee: 12501 lamports */
unsigned char txn2[543] = {
0x01,0xf6,0xd1,0xa2,0x56,0x4e,0x1f,0x5d,0xb3,0x01,0x38,0xf2,0x28,0xfc,0xa9,0x7e,
0xdc,0xc7,0x9c,0xd6,0x4c,0x49,0x3f,0xd9,0x84,0xa0,0x73,0x5b,0x96,0x8e,0xf9,0x5b,
0xe2,0xa1,0x05,0x6d,0xb5,0x32,0x04,0x2c,0x3c,0x31,0xfd,0x2b,0x1b,0xa6,0x55,0xc5,
0x66,0xd6,0xda,0xa3,0xa2,0xc2,0x93,0xe2,0xdf,0xa9,0xb0,0x13,0x35,0x02,0x7c,0x3a,
0x0b,0x80,0x01,0x00,0x02,0x03,0x05,0x2a,0x20,0x4c,0x36,0xe4,0xb8,0x06,0xce,0x32,
0xb5,0x39,0x47,0x4b,0x8e,0x6d,0xb7,0x89,0x55,0xe6,0x4b,0x66,0x04,0x3f,0xbb,0xa4,
0x31,0xef,0x28,0x9a,0x3d,0x30,0xc6,0x89,0x6d,0x1d,0xad,0x6d,0xcd,0x87,0xcd,0x94,
0x2b,0x31,0xf1,0x9b,0x6e,0xcf,0x6a,0x45,0x17,0x37,0x56,0x08,0x18,0xd4,0xa9,0xa6,
0x59,0xe6,0x59,0x0e,0xb4,0xea,0x03,0x06,0x46,0x6f,0xe5,0x21,0x17,0x32,0xff,0xec,
0xad,0xba,0x72,0xc3,0x9b,0xe7,0xbc,0x8c,0xe5,0xbb,0xc5,0xf7,0x12,0x6b,0x2c,0x43,
0x9b,0x3a,0x40,0x00,0x00,0x00,0x7b,0xf7,0xa0,0x15,0xa9,0xac,0xd5,0xc2,0x6a,0x64,
0xd5,0x70,0x29,0xd8,0x43,0x15,0x15,0x51,0xa6,0x73,0xa1,0x7b,0x72,0x2e,0xf2,0x28,
0x2b,0xec,0x57,0x91,0x65,0x23,0x03,0x01,0x28,0x19,0x1a,0x17,0x16,0x00,0x08,0x03,
0x07,0x06,0x04,0x05,0x05,0x19,0x1a,0x1b,0x1c,0x00,0x06,0x0b,0x0c,0x0f,0x0d,0x0e,
0x0e,0x18,0x00,0x0f,0x08,0x12,0x11,0x10,0x0a,0x09,0x13,0x15,0x14,0x1d,0x1a,0x1e,
0x0f,0x0e,0x05,0x11,0x8c,0xf5,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x09,
0x02,0x00,0x05,0x02,0x20,0xa1,0x07,0x00,0x02,0x00,0x09,0x03,0x99,0x3a,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x8a,0x23,0xa1,0x9f,0xe3,0xb6,0xb3,0x66,0x1e,0x03,0x79,
0x93,0x64,0x03,0x67,0xf7,0x71,0x42,0x69,0x51,0x84,0x0c,0xa3,0x30,0xf6,0x2e,0x0e,
0x25,0xdf,0x26,0xc2,0x91,0x05,0xeb,0xed,0xef,0xfb,0xec,0x02,0xe9,0xe8,0x91,0xdb,
0xde,0xa3,0x24,0x67,0x29,0xdd,0x0a,0xa0,0xbd,0x6d,0x7b,0x79,0x8e,0x8f,0x24,0x26,
0xc9,0x7f,0x16,0x6e,0xf2,0xad,0x7e,0xb9,0xf8,0xc8,0xe0,0xc6,0x3d,0xaa,0x01,0x08,
0x03,0x03,0x01,0x06,0x7b,0xc7,0x13,0x0d,0x9a,0xd1,0x6a,0xb9,0x22,0xf9,0x51,0x29,
0xeb,0x3f,0x1c,0x2c,0x6c,0x16,0x2d,0x7e,0x23,0xfa,0xfc,0x26,0x7c,0x48,0xb5,0xc8,
0x4b,0x21,0x1b,0xd9,0x02,0x23,0x22,0x00,0x83,0x31,0x40,0x8a,0x96,0xc8,0x53,0xff,
0xbb,0x12,0x14,0x05,0xbf,0xae,0xb3,0xb3,0x58,0x11,0x49,0x7f,0xf7,0x9b,0xa1,0x1d,
0xd2,0x71,0xef,0xd6,0x37,0x41,0x6d,0xc0,0x04,0xbd,0xbc,0xbf,0xc1,0x02,0xb9,0xba,
0xe7,0xe1,0x9f,0xad,0x30,0xca,0x1c,0x27,0x75,0xb7,0x31,0x75,0x12,0x83,0x0b,0xee,
0xb0,0x66,0xa7,0xc6,0xd6,0x58,0x4d,0xd8,0xf0,0x96,0x66,0x86,0x6c,0x70,0x65,0xe7,
0x01,0xf7,0x00,0xa4,0xaf,0x9d,0x79,0x68,0x5f,0x34,0x8e,0x06,0x64,0xaa,0xf7,0x24,
0x69,0xd7,0x8f,0x95,0xe2,0x57,0xa7,0xac,0xa1,0x50,0xb3,0x82,0xc3,0x84,0xea,0x72,
0xd6,0xc3,0xa4,0x06,0x99,0x98,0x97,0x9a,0x9c,0x9b,0x01,0x9d,0x03,0xbe,0xf1,0xa3,
0x34,0x0f,0xbb,0x79,0xeb,0xae,0xd7,0xd1,0x7d,0xd1,0x2c,0x5f,0x23,0x5d,0xc9,0xeb,
0x5d,0xee,0xbf,0x6f,0x5b,0x32,0x71,0x4f,0x23,0x2e,0x6b,0xbd,0x00,0x01,0xca};

/* Just 1M CU, no extra fee */
unsigned char txn3[683] = {
0x01,0x36,0x76,0xa3,0x72,0x35,0xb1,0xdb,0x3a,0xcb,0xf5,0xd1,0x60,0x7d,0x61,0x40,
0xd3,0x25,0x70,0x3e,0x81,0xd6,0x79,0x07,0x54,0xef,0xdb,0xa8,0xb0,0x0c,0x4b,0xe6,
0xd4,0x68,0x65,0x18,0x9f,0x6d,0xe5,0xd5,0xa5,0x2e,0x1f,0x05,0x3f,0x81,0x7a,0x1b,
0x2f,0xa4,0xc8,0xdd,0x21,0x57,0xe2,0x01,0x90,0x35,0x07,0xca,0xe8,0x9c,0x7c,0x1a,
0x06,0x01,0x00,0x05,0x10,0x98,0x63,0x71,0x34,0xb7,0xae,0x9f,0x06,0xb8,0x77,0xeb,
0x41,0x14,0xd1,0x9b,0x06,0xdf,0x83,0x5b,0x02,0xe1,0x07,0x25,0x91,0x60,0x92,0xc1,
0x1a,0x47,0xc3,0xe0,0x4a,0x1c,0x4d,0x84,0x4d,0x54,0x21,0x3f,0x6d,0x52,0x50,0xad,
0xb8,0x1f,0xa3,0xf0,0x46,0xfc,0xf2,0xaf,0x77,0x30,0xcf,0x2c,0x8a,0x24,0xcb,0xe6,
0x2a,0xa7,0x60,0x23,0x6b,0x2b,0x98,0x37,0x28,0x58,0xb3,0xe8,0x02,0xc6,0x8e,0xa0,
0x92,0x1b,0x25,0xe8,0xe2,0xf0,0x23,0x13,0x9b,0x62,0xbe,0x8c,0xc6,0x79,0xc3,0x84,
0x53,0x1a,0x27,0x94,0xcd,0x3a,0x5d,0xe5,0xd9,0x4e,0xe6,0xc1,0x67,0x87,0xd9,0x02,
0x5f,0x20,0x4e,0xd3,0x3c,0x17,0xfc,0x3d,0x55,0xe9,0x70,0xfd,0xb6,0x25,0x25,0x46,
0xf6,0xa1,0x79,0x81,0x71,0x4d,0x5b,0x7d,0x27,0xf0,0x0d,0x40,0x0e,0x69,0x00,0x69,
0xf1,0xbc,0xca,0xc2,0x81,0xe1,0xec,0xe5,0x98,0xd4,0xcc,0x76,0x21,0x70,0xd8,0xde,
0x86,0xc3,0xbb,0x41,0xde,0x55,0x6b,0xb3,0xaf,0x23,0xd8,0x79,0xc5,0x8f,0x44,0x83,
0x89,0x27,0x2e,0x84,0xe8,0x9e,0xab,0xb0,0x54,0x74,0x8a,0xb9,0x54,0x58,0x2f,0x92,
0xca,0x03,0xd7,0x0d,0xf9,0x71,0xab,0xea,0x22,0x60,0xef,0xba,0xa3,0x92,0x28,0x79,
0x11,0x33,0x9e,0xde,0x85,0x33,0x21,0xfd,0xa6,0xab,0x1e,0x3b,0xaa,0xc0,0x9a,0x8c,
0xaf,0xee,0xcb,0x7a,0x32,0x90,0x8e,0xd2,0xa9,0xd7,0x0f,0x7d,0x19,0xb2,0xd7,0x9f,
0xec,0x5b,0x57,0xb3,0xc0,0x01,0xbb,0x51,0x49,0x86,0x1d,0x23,0xef,0xd9,0x60,0x8b,
0x75,0x91,0x17,0xed,0xd2,0xb1,0x11,0x0e,0xad,0xc2,0x76,0xd3,0xe5,0x0f,0xc3,0x44,
0x44,0x8d,0x8e,0x3d,0x4d,0x5b,0x64,0x00,0xee,0x50,0x9a,0x59,0x51,0x7a,0xec,0x52,
0x35,0xed,0x4b,0xca,0x4b,0xc6,0x9d,0x77,0x8e,0x2d,0x0d,0x58,0x33,0x34,0xe1,0x12,
0x8f,0xda,0x66,0x46,0x74,0xbc,0x8a,0xbc,0x8d,0x22,0x07,0x6c,0x70,0x6c,0x32,0x3b,
0xf1,0x86,0x75,0xa0,0x06,0xf8,0x8f,0xf8,0x80,0x36,0xd7,0x1e,0x1b,0xc9,0xe1,0x35,
0x3a,0x75,0x65,0x02,0x45,0x65,0xcd,0x3f,0xe4,0x81,0x12,0x55,0x1b,0x26,0x98,0x93,
0xa5,0x74,0x5a,0xa2,0x7a,0x59,0x66,0x8c,0x25,0x62,0x37,0x28,0x19,0x7b,0x24,0x1f,
0x8d,0x9f,0x88,0x8e,0xbe,0x56,0xda,0xa9,0x03,0x6e,0x43,0x1e,0x97,0x83,0xbc,0x89,
0x49,0x1d,0x43,0xb7,0x8d,0x03,0x06,0x46,0x6f,0xe5,0x21,0x17,0x32,0xff,0xec,0xad,
0xba,0x72,0xc3,0x9b,0xe7,0xbc,0x8c,0xe5,0xbb,0xc5,0xf7,0x12,0x6b,0x2c,0x43,0x9b,
0x3a,0x40,0x00,0x00,0x00,0x06,0xa7,0xd5,0x17,0x19,0x2c,0x5c,0x51,0x21,0x8c,0xc9,
0x4c,0x3d,0x4a,0xf1,0x7f,0x58,0xda,0xee,0x08,0x9b,0xa1,0xfd,0x44,0xe3,0xdb,0xd9,
0x8a,0x00,0x00,0x00,0x00,0x08,0x41,0x3a,0xa6,0x21,0x31,0x0c,0x1f,0x15,0xb3,0x53,
0x5b,0x3f,0x3d,0x6c,0xd3,0x4e,0x1e,0xd7,0x46,0x7c,0xf1,0xe8,0x0f,0xf8,0x03,0x51,
0x02,0x64,0x88,0x84,0xfe,0x08,0x66,0x9c,0x91,0x98,0x54,0x4c,0x1f,0x62,0xdb,0xb6,
0x4e,0xe6,0x68,0x77,0xce,0x58,0x43,0xc7,0x44,0xb7,0x57,0x5d,0xa0,0xbd,0x7b,0x91,
0x62,0x52,0x3f,0x63,0xbd,0xce,0xe0,0x55,0x38,0xff,0xd7,0x5f,0xed,0x99,0x7d,0x80,
0xc1,0xcb,0xf4,0x44,0x89,0x1c,0x94,0x0b,0xb8,0x45,0x49,0x02,0x86,0xb7,0x32,0xdb,
0xd7,0x3a,0xf1,0x27,0x9f,0x02,0x0c,0x00,0x05,0x02,0x40,0x42,0x0f,0x00,0x0f,0x0e,
0x0b,0x0a,0x05,0x00,0x06,0x01,0x02,0x04,0x03,0x08,0x07,0x09,0x0e,0x0d,0x2c,0x45,
0xa1,0x5d,0xca,0x78,0x7e,0x4c,0xb9,0x00,0x29,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2f,0x59,0x5b,0x00,0x00,0x00,0x00,0x00,
0x01,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/* 1 M CU, 5 lamports extra (deprecated) */
unsigned char txn4[783] = {
0x01,0x9e,0x83,0xce,0xfa,0x47,0x4e,0x86,0x41,0xd2,0x1c,0x2d,0x29,0x2f,0x7d,0xde,
0x1e,0xa1,0x7f,0xd3,0xb4,0xfa,0x72,0x07,0xad,0xfb,0x9b,0x60,0xe3,0x1d,0x60,0x01,
0x5f,0x70,0x6f,0x99,0xbd,0x95,0x7b,0xdf,0x0e,0x8d,0xd5,0x27,0x24,0x92,0x69,0xf0,
0x14,0x49,0x33,0xa5,0xfe,0x64,0xf5,0x6e,0x22,0x05,0x41,0x7c,0xdc,0x7e,0xfc,0xed,
0x03,0x01,0x00,0x06,0x13,0xec,0x40,0xfc,0x11,0x7b,0x68,0x5b,0xa1,0x32,0x60,0x9a,
0x09,0x66,0x93,0x9e,0x54,0x06,0x6a,0x12,0x5f,0x7c,0x6e,0x6e,0x6d,0xff,0x2c,0x2c,
0x9e,0x32,0x1a,0x34,0xbf,0x0b,0x26,0xf6,0x60,0xe3,0xbf,0x82,0xb5,0x1f,0xdc,0x0d,
0x5e,0x27,0x2c,0x3a,0x52,0xea,0xe6,0x22,0x82,0x9c,0xa3,0x7c,0xe4,0x0c,0xb4,0x7b,
0xb1,0xa3,0xcd,0xcf,0xcc,0x8d,0x83,0x85,0x60,0x8b,0xdb,0x27,0x90,0x0a,0x0c,0xe3,
0x3d,0xbf,0x3c,0xca,0x79,0x7c,0x6e,0x89,0xe3,0x3e,0xa8,0x52,0xec,0xc6,0xf4,0xae,
0x8d,0x52,0xc0,0xd7,0xe3,0xf8,0x76,0xe7,0x0e,0x49,0x6e,0x7d,0x11,0x9a,0x5e,0x75,
0x67,0x04,0x3e,0x6f,0x15,0x62,0xb5,0xe4,0x8f,0x9b,0x13,0x33,0x01,0xb2,0xd8,0x45,
0x66,0x78,0xbd,0x00,0x95,0x4d,0x14,0xa9,0x42,0x80,0x3e,0xd9,0x37,0x3a,0x93,0xf2,
0x4d,0xcd,0x7e,0xf7,0xa1,0x37,0x84,0xc8,0x09,0xc9,0x8c,0x22,0xef,0xb7,0x60,0x8e,
0xec,0xda,0xd0,0xbe,0x36,0x87,0xa7,0x95,0xa1,0x23,0x62,0x20,0x9c,0x8f,0x81,0x5f,
0x93,0x4c,0x76,0x1e,0xb9,0x51,0x7d,0x05,0x8e,0x9e,0xf9,0x25,0x85,0xab,0xea,0xe5,
0x01,0xac,0xbe,0x15,0x06,0x58,0x36,0x47,0x2b,0xde,0x7d,0x79,0x58,0x1f,0x3a,0xaf,
0x98,0x6b,0x63,0xa7,0x27,0xd8,0xbd,0x67,0x1e,0xf7,0x58,0x82,0x8c,0x5c,0x16,0x29,
0xd4,0xe7,0x89,0xaf,0xea,0x4d,0xde,0xdc,0x50,0xef,0xcc,0x7c,0x5d,0x91,0x3a,0x23,
0x10,0x4d,0x04,0xae,0xa6,0x73,0x93,0xda,0x27,0x83,0x5f,0xda,0x11,0x99,0xfb,0xbd,
0x39,0xc9,0xda,0xcd,0xfb,0xef,0x22,0x13,0x99,0x3d,0xa5,0x9a,0x11,0x7e,0xc4,0x4e,
0xd5,0x3c,0x9f,0xbb,0xe4,0xb9,0xee,0xd6,0xdb,0x34,0xbb,0x41,0x53,0xba,0x36,0xb6,
0x1e,0xd1,0x02,0xa5,0x6c,0x4f,0xc6,0x95,0xb8,0x4c,0x7f,0x4a,0x4a,0x9d,0xb0,0xb1,
0xc6,0x95,0x70,0xbd,0xa1,0xd7,0x84,0x39,0x71,0x25,0xda,0x32,0xff,0xa5,0x9b,0x7b,
0xdb,0xf3,0x04,0x6c,0x4e,0xe7,0x12,0x80,0xb9,0xe2,0x70,0xb3,0x36,0xd8,0x88,0xfd,
0xfc,0xf7,0x47,0xea,0x01,0xed,0x56,0x65,0x46,0xea,0x14,0xfb,0x23,0x32,0xd4,0x0c,
0xf5,0x43,0xc8,0x0d,0x28,0x66,0x0e,0x34,0xdf,0x05,0xe2,0x31,0xb8,0x80,0x8a,0xb6,
0x35,0x8f,0x95,0x62,0xd5,0xc4,0x18,0x03,0x12,0x03,0x29,0x6d,0x19,0xbf,0x08,0xd2,
0x10,0x34,0x44,0xc0,0xa2,0xe1,0x90,0xab,0x12,0x1a,0x93,0xed,0xdf,0xf2,0x76,0x9b,
0x78,0xc0,0x0e,0x74,0x94,0x79,0xf6,0xf7,0xe7,0xbb,0xbf,0xd7,0xe0,0xe3,0xd8,0xc9,
0x28,0xe7,0x5f,0xde,0x3b,0x03,0x06,0x46,0x6f,0xe5,0x21,0x17,0x32,0xff,0xec,0xad,
0xba,0x72,0xc3,0x9b,0xe7,0xbc,0x8c,0xe5,0xbb,0xc5,0xf7,0x12,0x6b,0x2c,0x43,0x9b,
0x3a,0x40,0x00,0x00,0x00,0x20,0x95,0xdd,0x92,0x49,0x29,0xc6,0x68,0x2e,0x9f,0xf6,
0xc1,0x1b,0x0e,0x1b,0xdd,0xce,0xf2,0x9f,0x1a,0xd2,0x21,0x1e,0x89,0x2a,0x4f,0xb8,
0x8e,0xa5,0xd1,0xad,0xa1,0x85,0x0f,0x2d,0x6e,0x02,0xa4,0x7a,0xf8,0x24,0xd0,0x9a,
0xb6,0x9d,0xc4,0x2d,0x70,0xcb,0x28,0xcb,0xfa,0x24,0x9f,0xb7,0xee,0x57,0xb9,0xd2,
0x56,0xc1,0x27,0x62,0xef,0x06,0xdd,0xf6,0xe1,0xd7,0x65,0xa1,0x93,0xd9,0xcb,0xe1,
0x46,0xce,0xeb,0x79,0xac,0x1c,0xb4,0x85,0xed,0x5f,0x5b,0x37,0x91,0x3a,0x8c,0xf5,
0x85,0x7e,0xff,0x00,0xa9,0x06,0xa7,0xd5,0x17,0x19,0x2c,0x5c,0x51,0x21,0x8c,0xc9,
0x4c,0x3d,0x4a,0xf1,0x7f,0x58,0xda,0xee,0x08,0x9b,0xa1,0xfd,0x44,0xe3,0xdb,0xd9,
0x8a,0x00,0x00,0x00,0x00,0x8e,0x49,0x8f,0x61,0x98,0x49,0x25,0x4c,0x31,0x6b,0xad,
0x93,0x70,0x5d,0x16,0x07,0xbc,0xd8,0x02,0xbe,0x79,0x92,0x0a,0x47,0x32,0x13,0xf4,
0xb1,0x94,0x03,0x56,0xb1,0x54,0x68,0xa7,0xaa,0xc2,0xc3,0xc5,0xcc,0x88,0x83,0xd2,
0xbe,0x1d,0xb8,0x0e,0xfe,0x85,0x39,0xcc,0xb3,0x37,0x14,0xc3,0xfd,0x6c,0x61,0x7b,
0x84,0xdc,0x69,0xe2,0xcc,0x02,0x0d,0x00,0x09,0x00,0x40,0x42,0x0f,0x00,0x05,0x00,
0x00,0x00,0x12,0x11,0x00,0x0e,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,
0x0b,0x0c,0x0f,0x10,0x11,0x29,0xe0,0xbd,0x77,0x84,0xcf,0x36,0x13,0x17,0x01,0x20,
0xa1,0x07,0x00,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0xa0,0xbb,0x0d,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2f,0x63,0x15,0x00,0x00,0x00,0x00,0x00};

unsigned char parsed[FD_TXN_MAX_SZ];

void
test_txn( uchar * payload,
          ulong   payload_sz,
          ulong   expected_max_cu,
          ulong   expected_fee_lamports ) { /* Excludes per-signature fee */
  FD_TEST( fd_txn_parse( payload, payload_sz, parsed, NULL ) );
  fd_txn_t * txn = (fd_txn_t*)parsed;
  fd_compute_budget_program_state_t state;
  fd_compute_budget_program_init( &state );
  uchar * addresses = payload + txn->acct_addr_off;
  for( ulong i=0UL; i<txn->instr_cnt; i++ ) {
    if( !memcmp( addresses+FD_TXN_ACCT_ADDR_SZ*txn->instr[ i ].program_id, FD_COMPUTE_BUDGET_PROGRAM_ID, FD_TXN_ACCT_ADDR_SZ ) ) {
      FD_TEST( fd_compute_budget_program_parse( payload+txn->instr[ i ].data_off, txn->instr[ i ].data_sz, &state ) );
    }
  }
  ulong rewards = 0UL;
  uint  compute = 0U;
  fd_compute_budget_program_finalize( &state, txn->instr_cnt, &rewards, &compute );
  FD_TEST( rewards==expected_fee_lamports );
  FD_TEST( (ulong)compute==expected_max_cu );
}

FD_FN_CONST int
test_duplicate( ulong request_units_deprecated_cnt,
                ulong request_heap_frame_cnt,
                ulong set_compute_unit_limit_cnt,
                ulong set_compute_unit_price_cnt ) {
  uchar const request_units_deprecated[ 9UL ] = { 0, 4,3,2,1, 8,7,6,5 };
  uchar const request_heap_frame      [ 5UL ] = { 1, 0,0,1,0          };
  uchar const set_compute_unit_limit  [ 5UL ] = { 2, 4,3,2,1          };
  uchar const set_compute_unit_price  [ 9UL ] = { 3, 8,7,6,5,4,3,2,1  };
  fd_compute_budget_program_state_t state;
  fd_compute_budget_program_init( &state );

  int all_valid = 1;
  for( ulong i=0UL; i<request_units_deprecated_cnt; i++ )
    all_valid &= fd_compute_budget_program_parse( request_units_deprecated, 9UL, &state );
  for( ulong i=0UL; i<request_heap_frame_cnt;       i++ )
    all_valid &= fd_compute_budget_program_parse( request_heap_frame,       5UL, &state );
  for( ulong i=0UL; i<set_compute_unit_limit_cnt;   i++ )
    all_valid &= fd_compute_budget_program_parse( set_compute_unit_limit,   5UL, &state );
  for( ulong i=0UL; i<set_compute_unit_price_cnt;   i++ )
    all_valid &= fd_compute_budget_program_parse( set_compute_unit_price,   9UL, &state );
  return all_valid;
}

int
main( int     argc,
      char ** argv ) {
  fd_boot( &argc, &argv );

  fd_rng_t _rng[1]; fd_rng_t * rng = fd_rng_join( fd_rng_new( _rng, 0U, 0UL ) );

  test_txn( txn1, sizeof(txn1),  700000UL,    0UL );
  test_txn( txn2, sizeof(txn2),  500000UL, 7501UL );
  test_txn( txn3, sizeof(txn3), 1000000UL,    0UL );
  test_txn( txn4, sizeof(txn4), 1000000UL,    5UL );

  uint  * cu_limit  = (uint  *) &txn2[ 260 ];
  ulong * ulamports = (ulong *) &txn2[ 268 ];
  *cu_limit = 1000000U; *ulamports = 1000000UL;    test_txn( txn2, sizeof(txn2), 1000000UL, 1000000UL       ); /* No overflow  */
  *cu_limit = 1000000U; *ulamports = ULONG_MAX>>1; test_txn( txn2, sizeof(txn2), 1000000UL, ULONG_MAX>>1    ); /* Product>2^64 */
  *cu_limit = 2000000U; *ulamports = ULONG_MAX;    test_txn( txn2, sizeof(txn2), 2000000UL, ULONG_MAX       ); /* Result>2^64  */
  *cu_limit = 9000000U; *ulamports = 1UL<<40;      test_txn( txn2, sizeof(txn2), 9000000UL, 9895604649984UL ); /* Product<2^64 */
  *cu_limit =       1U; *ulamports = 1UL;          test_txn( txn2, sizeof(txn2),       1UL, 1UL             ); /* Test ceil    */

  FD_TEST( test_duplicate( 1, 1, 0, 0 ) == 1 );
  FD_TEST( test_duplicate( 2, 0, 0, 0 ) == 0 );
  FD_TEST( test_duplicate( 0, 1, 1, 1 ) == 1 );
  FD_TEST( test_duplicate( 1, 1, 1, 1 ) == 0 );
  FD_TEST( test_duplicate( 0, 0, 2, 1 ) == 0 );
  FD_TEST( test_duplicate( 0, 0, 1, 2 ) == 0 );
  FD_TEST( test_duplicate( 1, 0, 1, 0 ) == 0 );
  FD_TEST( test_duplicate( 1, 0, 0, 1 ) == 0 );

  fd_rng_delete( fd_rng_leave( rng ) );

  FD_LOG_NOTICE(( "pass" ));
  fd_halt();
  return 0;
}

