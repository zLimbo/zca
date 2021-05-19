#include <openssl/conf.h>

int main()

{

    CONF *conf;

    BIO *bp;

    STACK_OF(CONF_VALUE) * v;

    CONF_VALUE *one;

    int i, num;

    long eline;

    conf = NCONF_new(NULL);

    bp = BIO_new_file("openssl.cnf", "r");

    if (bp == NULL)

    {

        printf("err!\n");

        return -1;
    }

    NCONF_load_bio(conf, bp, &eline);

    v = NCONF_get_section(conf, "CA_default");

    num = sk_CONF_VALUE_num(v);

    printf("section CA_default :\n");

    for (i = 0; i < num; i++)

    {

        one = sk_CONF_VALUE_value(v, i);

        printf("%s = %s\n", one->name, one->value);
    }

    BIO_free(bp);

    printf("\n");

    return 0;
}

// #include <openssl/conf.h>

// int main()

// {

//     CONF *conf;

//     long eline, result;

//     int ret;

//     char *p;

//     BIO *bp;

//     conf = NCONF_new(NULL);

// #if 0

//               bp=BIO_new_file("openssl.cnf","r");

//               NCONF_load_bio(conf,bp,&eline);

// #else

//     ret = NCONF_load(conf, "openssl.cnf", &eline);

//     if (ret != 1)

//     {

//         printf("err!\n");

//         return -1;
//     }

// #endif

//     p = NCONF_get_string(conf, NULL, "certs");

//     if (p == NULL)

//         printf("no global certs info\n");

//     p = NCONF_get_string(conf, "CA_default", "certs");

//     printf("%s\n", p);

//     p = NCONF_get_string(conf, "CA_default", "default_days");

//     printf("%s\n", p);

//     ret = NCONF_get_number_e(conf, "CA_default", "default_days", &result);

//     printf("%ld\n", result);

//     ret = NCONF_get_number(conf, "CA_default", "default_days", &result);

//     printf("%ld\n", result);

//     NCONF_free(conf);

//     return 0;
// }