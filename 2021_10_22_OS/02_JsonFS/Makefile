all:
	@echo -e "Использовать так:\n" \
	"\tmount - подключить файловую систему\n" \
	"\tumount - отключить файловую систему\n"
mount:
	mkdir -p mnt
	python3 driver.py mnt
umount:
	fusermount -u mnt
