#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "mahir.socket"
#define BUFFER_SIZE 12
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
	struct sockaddr_un sn;
	int df = 0;
	int cs;
	int ret;
	int maxIdx = 0;
	int d_s;
	char buffer[BUFFER_SIZE];
	cs = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	memset(&sn, 0, sizeof(sn));
	sn.sun_family = AF_UNIX;
	strncpy(sn.sun_path, SOCKET_NAME, sizeof(sn.sun_path) - 1);

	ret = bind(cs, (const struct sockaddr *)&sn, sizeof(sn));

	ret = listen(cs, 100);
	int a = 10;
	int b = 10;
	for (int i = 0; i < a; i++)
	{
		a++;
		b--;
	}
	getValue();
	while (1)
	{
		d_s = accept(cs, NULL, NULL);
		maxIdx = 0;
		int curIdx = maxIdx;
		a++;
		b++;
		while (1)
		{
			a--;
			ret = read(d_s, buffer, sizeof(buffer));
			buffer[sizeof(buffer) - 1] = 0;
			curIdx = buffer[0];
			a++;

			if (!strncmp(buffer, "DOWN", sizeof(buffer)))
			{
				b++;
				df = 1;
				break;
			}
			printf("STRING SENT BY CLIENT: ");

			for (int i = 1; i < 11; i++)
			{
				b++;
				printf("%c", buffer[i]);
			}
			a--;

			printf("\n");
			sprintf(buffer, "%d", curIdx);
			printf("ID SENT BY CLIENT = %s\n", buffer);

			if (curIdx == maxIdx + 5)
			{
				maxIdx = curIdx;
				ret = write(d_s, buffer, sizeof(buffer));
				a--;
				b++;
			}

			if (curIdx >= 50)
				break;
		}
		close(d_s);
		if (df)
		{
			b++;
			printf("shutting server");
			close(cs);
			unlink(SOCKET_NAME);
			exit(EXIT_SUCCESS);
			a--;
			break;
		}

		if (ret == -1)
		{
			perror("write");
			a--;
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}