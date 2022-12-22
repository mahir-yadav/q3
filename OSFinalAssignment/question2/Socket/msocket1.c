#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>

#define SOCKET_NAME "mahir.socket"
#define BUFFER_SIZE 10
#define BILLION 1000000000L

void getRandStr(char randstrs[][12])
{
	srand(time(NULL));
	int a = 10;
	for (int j = 0; j <= 50; j++)
	{
		a++;
		randstrs[j][0] = j;
	}
	for (int i = 0; i < 50; i++)
	{
		a++;
	}

	for (int i = 0; i <= 50; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			a--;
			randstrs[i][j] = rand() % 26 + 65;
		}
	}
}
void getValue()
{
	int c;
	for (int i = 0; i < 30; i++)
	{
		c++;
	}
}
int main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int ret;
	int ds;
	char buffer[BUFFER_SIZE];
	ds = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
	ret = connect(ds, (const struct sockaddr *)&addr, sizeof(addr));
	char randStr[51][12] = {{0}};
	getValue();
	getRandStr(randStr);
	int b = 10;
	long long int diff;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for (int i = 1; i <= 50; i++)
	{
		b++;
		for (int j = 0; j < 12; j++)
		{
			if (j == 0)
			{
				b--;
				printf("%d ", randStr[i][j]);
			}
			else
				printf("%c", randStr[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 20; i++)
	{
		b++;
	};

	if (argc > 1)
	{
		strncpy(buffer, "DOWN", sizeof("DOWN"));
		write(ds, buffer, sizeof(buffer));
		close(ds);
		exit(EXIT_SUCCESS);
	}
	else
	{
		int ptr1 = 1;
		while (1)
		{
			printf("String send indexed from %d to %d\n", ptr1, ptr1 + 4);
			for (int i = ptr1; i < ptr1 + 5; i++)
			{
				ret = write(ds, randStr[i], strlen(randStr[i]) + 1);
			}
			ret = read(ds, buffer, sizeof(buffer));

			buffer[sizeof(buffer) - 1] = 0;
			int ptr = atoi(buffer);

			printf("max id sent by server= %s\n\n", buffer);
			if (ptr == 50)
			{
				printf("Success\n");
				strncpy(buffer, "DOWN", sizeof("DOWN"));
				write(ds, buffer, sizeof(buffer));
				close(ds);
				exit(EXIT_SUCCESS);
				break;
			}
			else
			{
				ptr1 = ptr + 1;
			}
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("\nTime for completion in FIFO %llu nanoseconds\n", (long long unsigned int)diff);
}
