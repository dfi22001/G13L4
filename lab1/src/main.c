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
	int err;

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

//bt_conn_auth_cb_register(&auth_cb_display);

	bt_addr_le_t addr;
	char addr_s[BT_ADDR_LE_STR_LEN];
	size_t id_count = 1;
	bt_id_get(&addr, &id_count);
	bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));
	printk("addr: %s", addr_s);


	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(1));

		/* Heartrate measurements simulation */
		hrs_notify();

		/* Battery level simulation */
		bas_notify();
	}
}
