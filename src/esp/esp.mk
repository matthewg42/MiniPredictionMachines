# Either define ESP_MAKEFILE in the environment to be the full path 
# to where you have makeEspArduino.mk installed, or just edit it here...
ifndef ESP_MAKEFILE
	ESP_MAKEFILE := /opt/makeEspArduino/makeEspArduino.mk
endif

include $(ESP_MAKEFILE)


