#ifndef BASE64_H
#define BASE64_H

void base64_encrypt_text(const char *pbuf, int plen);

void base64_decrypt_text(const char *buf, int clen);

void base64_encrypt(const char *pbuf, char *cbuf);

void base64_decrypt(const char *buf, char *pbuf);

void show_base64(const char *buf, int len);
#endif

