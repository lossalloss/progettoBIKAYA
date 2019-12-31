
default:
	@echo "Please specify a target"

#clean della cartella e poi esegue il makefile di umps (umpsmake)
umps:   clean
	$(MAKE) -f umpsmake
#clean della cartella e poi esegue il makefile di uarm (uarmmake)
uarm:   clean
	$(MAKE) -f uarmmake
#clean della cartella
clean:
	$(MAKE) -f uarmmake clean
	$(MAKE) -f umpsmake clean

.PHONY: umps uarm
