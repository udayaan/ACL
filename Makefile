comp:
	gcc -o do_exec do_exec.c
	sudo chown root do_exec
	sudo chgrp root do_exec
	sudo chmod u+s do_exec
	gcc -o setacl.o setacl.c
	sudo chown root setacl.o
	sudo chgrp root setacl.o
	sudo chmod u+s setacl.o
	gcc -o getacl.o getacl.c
	sudo chown root getacl.o
	sudo chgrp root getacl.o
	sudo chmod u+s getacl.o
	gcc -o fput.o fput.c
	sudo chown root fput.o
	sudo chgrp root fput.o
	sudo chmod u+s fput.o
	gcc -o ls.o ls.c
	sudo chown root ls.o
	sudo chgrp root ls.o
	sudo chmod u+s ls.o
	gcc -o fget.o fget.c
	sudo chown root fget.o
	sudo chgrp root fget.o
	sudo chmod u+s fget.o
	gcc -o create_dir.o create_dir.c
	sudo chown root create_dir.o
	sudo chgrp root create_dir.o
	sudo chmod u+s create_dir.o

init:
	sudo mkdir /simple_slash
	sudo mkdir /simple_slash/home
	sudo chown root /simple_slash
	sudo chown root /simple_slash/home
	sudo groupadd simple_slash
	sudo chgrp simple_slash /simple_slash
	sudo chgrp simple_slash /simple_slash/home

addusers:
	sudo useradd -m -d /simple_slash/home/larry larry
	cat passwords | sudo passwd larry
	sudo useradd -m -d /simple_slash/home/nirav nirav
	cat passwords | sudo passwd nirav
	sudo useradd -m -d /simple_slash/home/sarah sarah
	cat passwords | sudo passwd sarah
	sudo useradd -m -d /simple_slash/home/bill bill
	cat passwords | sudo passwd bill
	sudo useradd -m -d /simple_slash/home/steve steve
	cat passwords | sudo passwd steve
	sudo useradd -m -d /simple_slash/home/mukesh mukesh
	cat passwords | sudo passwd mukesh
	sudo useradd -m -d /simple_slash/home/azim azim
	cat passwords | sudo passwd azim
	sudo useradd -m -d /simple_slash/home/mark mark
	cat passwords | sudo passwd mark

delusers:
	sudo userdel larry
	sudo userdel nirav
	sudo userdel sarah
	sudo userdel bill
	sudo userdel steve
	sudo userdel mukesh
	sudo userdel azim
	sudo userdel mark

uninstall:
	sudo groupdel simple_slash
	sudo rm -r /simple_slash
	