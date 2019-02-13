/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Descriptors for keyboard Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t keyboard_DeviceDescriptor[keyboard_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength ���ȣ��豸�������ĳ���*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType ���ͣ��豸�������ķ�����0x01*/
    0x00,                       /*bcdUSB ʹ�õ�usb�汾*/
    0x02,
    0x00,                       /*bDeviceClass �豸ʹ�õ������*/
    0x00,                       /*bDeviceSubClass �豸ʹ�õ��������*/
    0x00,                       /*bDeviceProtocol �豸ʹ�õ�Э��*/
    0x08,                       /*bMaxPacketSize ��������*/
    0x1D,                       /*idVendor  ����ID*/
    0x09,
    0x0A,                       /*idProduct =  ��ƷID*/
    0x1A,
    0x00,                       /*bcdDevice rel. 1.00 �豸�汾��*/
    0x01,
    1,                          /*Index of string descriptor describing
                                              manufacturer �����ַ������� */
    2,                          /*Index of string descriptor describing
                                             product ��Ʒ�ַ�������*/
    3,                          /*Index of string descriptor describing the
                                             device serial number �豸���к��ַ�������*/
    0x01                        /*bNumConfigurations �豸��һ������*/
  }
  ; /* keyboard_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t keyboard_ConfigDescriptor[keyboard_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    keyboard_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xC0,         /* bmAttributes: Self powered �豸���� D7����λ1��D6�Ƿ��Թ��硢D5Զ�̻��ѡ���5λ����λ0*/
    0x96,         /* MaxPower 100(0x32) mA: this current is used for detecting Vbus */

    /************** Descriptor of Custom HID interface ****************/
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x01,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x01,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    /* 18 */
    0x09,         /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x21,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    keyboard_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom HID endpoints ******************/
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

    0x81,          /* bEndpointAddress: Endpoint Address (IN) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    0x08,          /* wMaxPacketSize: 8 Bytes max */
    0x00,
    0x20,          /* bInterval: Polling Interval (32 ms) */
    /* 34 */
    	
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
			/*	Endpoint descriptor type */
    0x01,	/* bEndpointAddress: */
			/*	Endpoint Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x01,	/* wMaxPacketSize: 2 Bytes max  */
    0x00,
    0x20,	/* bInterval: Polling Interval (20 ms) */
    /* 41 */
  }
  ; /* MOUSE_ConfigDescriptor */
const uint8_t keyboard_ReportDescriptor[keyboard_SIZ_REPORT_DESC] =
  {
     0x05, 0x01, // USAGE_PAGE (Generic Desktop)
 0x09, 0x06, // USAGE (Keyboard)
 0xa1, 0x01, // COLLECTION (Application)
 0x05, 0x07, //     USAGE_PAGE (Keyboard/Keypad)
 0x19, 0xe0, //     USAGE_MINIMUM (Keyboard LeftControl)
 0x29, 0xe7, //     USAGE_MAXIMUM (Keyboard Right GUI)
 0x15, 0x00, //     LOGICAL_MINIMUM (0)
 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
 0x95, 0x08, //     REPORT_COUNT (8)
 0x75, 0x01, //     REPORT_SIZE (1)
 0x81, 0x02, //     INPUT (Data,Var,Abs)
 0x95, 0x01, //     REPORT_COUNT (1)
 0x75, 0x08, //     REPORT_SIZE (8)
 0x81, 0x03, //     INPUT (Cnst,Var,Abs)
 0x95, 0x06, //   REPORT_COUNT (6)
 0x75, 0x08, //   REPORT_SIZE (8)
 0x25, 0xFF, //   LOGICAL_MAXIMUM (255)
 0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
 0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
 0x81, 0x00, //     INPUT (Data,Ary,Abs)
 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
 0x95, 0x02, //   REPORT_COUNT (2)
 0x75, 0x01, //   REPORT_SIZE (1)
 0x05, 0x08, //   USAGE_PAGE (LEDs)
 0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
 0x29, 0x02, //   USAGE_MAXIMUM (Caps Lock)
 0x91, 0x02, //   OUTPUT (Data,Var,Abs)
 0x95, 0x01, //   REPORT_COUNT (1)
 0x75, 0x06, //   REPORT_SIZE (6)
 0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
 0xc0        // END_COLLECTION
 }; /* keyboard_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t keyboard_StringLangID[keyboard_SIZ_STRING_LANGID] =
  {
    keyboard_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t keyboard_StringVendor[keyboard_SIZ_STRING_VENDOR] =
  {
    keyboard_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'G', 0, 'A', 0, 'R', 0, 'S', 0, 'O', 0, 'N', 0, 'P', 0, 'R', 0,
    'O', 0, 'D', 0, 'U', 0, 'C', 0, 'T', 0, 'I', 0, 'O', 0, 'N', 0
  };

const uint8_t keyboard_StringProduct[keyboard_SIZ_STRING_PRODUCT] =
  {
    keyboard_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'O', 0, 'S', 0, 'U', 0, ' ', 0, 'K', 0, 'E', 0, 'Y', 0, 'B', 0, 'O', 0, 'A', 0, 'R', 0, 'D', 0
  };
uint8_t keyboard_StringSerial[keyboard_SIZ_STRING_SERIAL] =
  {
    keyboard_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    '2', 0, '0', 0, '1', 0, '9', 0, '1', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

