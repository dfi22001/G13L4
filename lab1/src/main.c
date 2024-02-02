/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include "bt_stuff.h"


void main(void)
{

  uint8_t heartrate = 0U;
	uint8_t status = turn_on_bt();
	if (!status){
		printk("BT seems to have started just fine \n");
	} else {
		printk("oh shit!\n");
	}

	while (1) {
		heartrate++;
		bt_hrs_notify(heartrate);
		k_sleep(K_SECONDS(1));
	}
}
