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
	