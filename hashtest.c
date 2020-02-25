#include <stdio.h>

int data[1024 * 1024];


int argv_to_int(char *argv)
{
	printf("argv[1] = '%s' (%d)\n", argv, *argv);
	char *p;
	long num = strtol(argv, &p, 10);
	return num;
}

/* 1st arg: Folding or Nonfloding hash */
/* 2nd arg: dump to csv */
int main(int argc, char **argv)
{
        unsigned short src, dst;
        unsigned long hash;
	FILE *fp;
	int hash_fold = 1;

	if (argc > 1) {
		if (1 == argv_to_int(argv[1]))
			hash_fold = 0;
	}
        printf("%s hash\n", hash_fold ? "Folding" : "Non-folding");
	
	if (argc > 2) {
		fp = fopen("/tmp/hashout.csv", "w");
        	printf("dump output to csv: /tmp/hashout.csv\n");
	}

	if (argc > 2) {
        	fprintf(fp, "%s hash\nbucket,hits\n", hash_fold ? "Folding" : "Non-folding");
	} else {
        	printf("%s hash\nbucket\thits\n", hash_fold ? "Folding" : "Non-folding");
	}

        for (src = 0x8000; src < 0xFFFE; src++)
                for (dst = 0x0400; dst <= 0xFFFE; dst++) {
                        hash = src * 31 + dst;
                        if (hash_fold) {
                                hash ^= hash >> 16;
                                hash ^= hash >> 8;
                        }
                        hash &= 0xFFFFF;
                        data[hash]++;
                }
        int i, c=0;
        for (i = 0; i < 1024 * 1024; i++) {
		int d = data[i];
		c++;
		if (argc > 2) {
			fprintf(fp, "%d,%d\n", i, d);
		} else {
			printf("%#x\t%d\n", i, d);
		}
	}

	if (argc > 2) {
		fprintf(fp, "c=%d\n", c);
		fclose(fp);
	} else {
		printf("c=%d\n", c);
	}

        return 0;
}
