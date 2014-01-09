zy2170
Zuokun Yu
Lab5
Code works as specified in the lab. Majority of code in nc-2 was sourced from
nc-1.

The only thing that might be weird is that I used sleep() to delay the parent
process due to formatting issues.

 PPID   PID  PGID   SID TTY      TPGID STAT   UID   TIME COMMAND
    0     1     1     1 ?           -1 Ss       0   0:56 /sbin/init
    1   859   859   859 ?           -1 Ss       0   0:04 /usr/sbin/sshd -D
  859 16413 16413 16413 ?           -1 Ss       0   0:00  \_ sshd: zy2170[priv]
16413 16436 16413 16413 ?           -1 S    15004   0:00  |   \_ sshd:zy2170@pts/2
16436 16442 16442 16442 pts/2    16668 Ss   15004   0:00  |       \_ -bash
16442 16668 16668 16442 pts/2    16668 S+   15004   0:00  |           \_./mdb-lookup-server-nc-1 8890
16668 16669 16668 16442 pts/2    16668 S+   15004   0:00  |               \_ /bin/bash ./mdb-lookup-server-nc.sh 8890
16669 16671 16668 16442 pts/2    16668 S+   15004   0:00  |		     \_ cat mypipe-16669
16669 16672 16668 16442 pts/2    16668 S+   15004   0:00  |		     \_ nc -l 8890
16669 16673 16668 16442 pts/2    16668 S+   15004   0:00  |		     \_ /bin/sh /home/jae/cs3157-pub/bin/mdb-lookup-cs3157
16673 16674 16668 16442 pts/2    16668 S+   15004   0:00  |			\_ /home/jae/cs3157-pub/bin/mdb-lookup /home/jae/cs3157-pub/bin/mdb-cs3157

Two shell scripts 
1) /bin/bash ./mdb-lookup-server-nc.sh 8890
2) /bin/sh /home/jae/cs3157-pub/bin/mdb-lookup-cs3157
