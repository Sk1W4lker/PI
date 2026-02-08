void triangulo(int n) {
    for (int i = 1; i <= n; i++) {

        int espacos = n - i;
        int hashes  = 2 * i - 1;

        for (int s = 0; s < espacos; s++)
            putchar(' ');

        for (int h = 0; h < hashes; h++)
            putchar('#');

        putchar('\n');
    }
}

