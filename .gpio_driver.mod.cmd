savedcmd_/home/wang/gpio_driver/gpio_driver.mod := printf '%s\n'   gpio_driver.o | awk '!x[$$0]++ { print("/home/wang/gpio_driver/"$$0) }' > /home/wang/gpio_driver/gpio_driver.mod
