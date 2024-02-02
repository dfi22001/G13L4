#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include "bt_stuff.h"



static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

//void hrs_notify(void)
//{


	/* Heartrate measurements simulation */
//	heartrate++;
//	if (heartrate == 160U) {
//		heartrate = 90U;
//	}

//	bt_hrs_notify(heartrate);
//}

uint8_t turn_on_bt(void)
{
	int err;
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 1;
	}

	bt_ready();
	bt_addr_le_t addr;
	char addr_s[BT_ADDR_LE_STR_LEN];
	size_t id_count = 1;
	bt_id_get(&addr, &id_count);
	bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));
	printk("addr: %s", addr_s);
	return 0;


}
