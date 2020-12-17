int rising_hope(char *R) {
    int sum=0;

    while (*R) {
        if (*R=='P') sum++;
        if (*R=='N') sum--;

        *R++;
    }

    return sum;
}
