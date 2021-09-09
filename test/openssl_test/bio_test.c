#include <stdio.h>

#include <openssl/bio.h>

int test_bio_mem();
int test_bio_file();


int main() {

    test_bio_file();
    return 0;
}

int test_bio_file()

{

    BIO *b = NULL;

    int len = 0, outlen = 0;

    char *out = NULL;

    b = BIO_new_file("bf.txt", "w");

    len = BIO_write(b, "openssl", 4);

    len = BIO_printf(b, "%s", "zcp");

    BIO_free(b);

    b = BIO_new_file("bf.txt", "r");

    len = BIO_pending(b);

    len = 50;

    out = (char *)OPENSSL_malloc(len);

    len = 1;

    while (len > 0)

    {

        len = BIO_read(b, out + outlen, 1);

        outlen += len;
    }

    BIO_free(b);

    printf("out = %s\n", out);

    free(out);

    return 0;
}

int test_bio_mem()

{

    BIO *b = NULL;

    int len = 0;

    char *out = NULL;

    b = BIO_new(BIO_s_mem());

    len = BIO_write(b, "openssl", 4);

    len = BIO_printf(b, "%s", "zcp");

    len = BIO_ctrl_pending(b);

    out = (char *)OPENSSL_malloc(len);

    len = BIO_read(b, out, len);

    printf("out: %s\n", out);

    OPENSSL_free(out);

    BIO_free(b);

    return 0;
}