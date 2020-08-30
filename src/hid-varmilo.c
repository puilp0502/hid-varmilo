// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  HID report fixup for varmilo keyboards
 *
 *  Copyright (c) 2020 Frank Yang <puilp0502@gmail.com>
 *
 */

#include <linux/hid.h>
#include <linux/module.h>

#include "hid-ids.h"

/*
 * Varmilo VA104M with device ID of 07B1 incorrectly reports Logical Minimum as
 * 572 (0x02 0x3c). We fix this by setting Logical Minimum to zero.
 */
static __u8 *varmilo_07b1_report_fixup(struct hid_device *hdev, __u8 *rdesc,
                                      unsigned int *rsize)
{
       if (*rsize == 25 &&
           rdesc[0] == 0x05 && rdesc[1] == 0x0c &&
           rdesc[2] == 0x09 && rdesc[3] == 0x01 &&
           rdesc[6] == 0x19 && rdesc[7] == 0x00 &&
           rdesc[11] == 0x16 && rdesc[12] == 0x3c && rdesc[13] == 0x02) {
               hid_info(hdev,
                        "fixing up varmilo VA104M consumer control report descriptor\n");
               rdesc[12] = 0x00;
               rdesc[13] = 0x00;
       }
       return rdesc;
}

static __u8 *varmilo_report_fixup(struct hid_device *hdev, __u8 *rdesc,
                                 unsigned int *rsize)
{
       if (hdev->product == USB_DEVICE_ID_VARMILO_VA104M_07B1 &&
           hdev->vendor == USB_VENDOR_ID_CYPRESS)
               rdesc = varmilo_07b1_report_fixup(hdev, rdesc, rsize);
       return rdesc;
}

static const struct hid_device_id varmilo_devices[] = {
       { HID_USB_DEVICE(USB_VENDOR_ID_CYPRESS, USB_DEVICE_ID_VARMILO_VA104M_07B1) },
       {}
};

MODULE_DEVICE_TABLE(hid, varmilo_devices);

static struct hid_driver varmilo_driver = {
       .name = "varmilo",
       .id_table = varmilo_devices,
       .report_fixup = varmilo_report_fixup,
};

module_hid_driver(varmilo_driver);

MODULE_LICENSE("GPL");
