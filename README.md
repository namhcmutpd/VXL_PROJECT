# 🚦 STM32 Traffic Light Control System
GVHD: Dr LE TRONG NHAN

Dự án mô phỏng hệ thống điều khiển đèn giao thông tại ngã tư sử dụng vi điều khiển **STM32F103RB**, áp dụng mô hình **Máy trạng thái hữu hạn (FSM)** để quản lý luồng hoạt động và **LCD 16x2 (I2C)** để hiển thị thông tin.

## 🛠 Phần cứng & Công cụ

* **MCU:** STM32F103RB (Kit Nucleo-F103RB).
* **Hiển thị:** LCD 1602 sử dụng giao tiếp I2C.
* **Đèn:** 2 Module đèn giao thông (hoặc 6 LED đơn: 2 Đỏ, 2 Vàng, 2 Xanh).
* **Input:** 4 Nút nhấn (Mode, Up, Down, Error).
* **IDE:** STM32CubeIDE.

## 🔌 Sơ đồ chân (Pin Configuration)

Cấu hình chân được định nghĩa trong `main.h` và `stm32f1xx_hal_msp.c`:

| Thành phần     | Chức năng | Chân MCU | Ghi chú                                   |
| :------------- | :-------- | :------- | :---------------------------------------- |
| **I2C LCD** | I2C1_SCL  | **PB8** |           |
|                | I2C1_SDA  | **PB9** |           |
| **Đèn Road 1** | Control A | **PA8** |                        |
|                | Control B | **PA9** |                        |
| **Đèn Road 2** | Control A | **PB4** |                        |
|                | Control B | **PB10** |                        |
| **Nút nhấn** | BTN_MODE  | **PA0** | Chuyển chế độ / Chọn   |
|                | BTN_UP    | **PA1** | Tăng giá trị           |
|                | BTN_DOWN  | **PA4** | Giảm giá trị           |
|                | BTN_ER    | **PB0** | Chế độ lỗi (Error)     |
| **Debug** | Blinky LED| **PA5** | LED tích hợp trên Kit  |

## ⚙️ Chế độ hoạt động (Modes)

Hệ thống hoạt động dựa trên 4 trạng thái FSM chính:

1.  **AUTO Mode (Mặc định):**
    * Chạy chu trình đèn giao thông tiêu chuẩn (Đỏ -> Xanh -> Vàng).
    * Đếm ngược thời gian hiển thị trên LCD.
    * Chuyển sang *Manual* bằng cách giữ nút Mode (1s).
    * Chuyển sang *Error* bằng cách giữ nút Error (1s).

2.  **MANUAL Mode (Cài đặt):**
    * Điều chỉnh thời gian đèn Đỏ và Xanh (Đèn Vàng được tính toán tự động hoặc cố định).
    * Sử dụng nút **UP/DOWN** để tăng giảm thời gian.
    * Nhấn **Mode** để chuyển giữa chỉnh Đỏ/Xanh.
    * Giữ **Mode** (1s) để lưu và quay về *Auto*.

3.  **ERROR Mode (Sự cố):**
    * Đèn Vàng ở cả 2 đường nhấp nháy liên tục (2Hz).
    * LCD hiển thị cảnh báo lỗi.
    * Giữ **Mode** (1s) để Reset về *Auto*.

4.  **INIT Mode:** Trạng thái khởi động, thiết lập thông số ban đầu.

## 📂 Cấu trúc dự án

* **Core:**
    * `main.c`: Vòng lặp chính, khởi tạo HAL và điều phối FSM.
    * `GLOBAL.h/.c`: Khai báo biến toàn cục và định nghĩa trạng thái.
* **FSM (Logic):**
    * `FSM_AUTO.c`: Logic chạy tự động.
    * `FSM_MANUAL.c`: Logic cài đặt thời gian.
    * `FSM_ERROR.c`: Logic báo lỗi.
* **Drivers/Modules:**
    * `LCD.c`: Driver điều khiển LCD 16x2 qua I2C (có cơ chế caching hiển thị).
    * `BUTTON.c`: Xử lý chống rung và phát hiện nhấn giữ nút.
    * `SOFTWARE_TIMER.c`: Bộ định thời mềm thay thế HAL_Delay.
    * `STATUS_LIGHT.c`: Điều khiển trạng thái bật/tắt các đèn LED.

## 🚀 Cách sử dụng

1.  Kết nối phần cứng theo bảng Pin Configuration.
2.  Mở dự án bằng **STM32CubeIDE**.
3.  Build và nạp code vào board Nucleo.
4.  Hệ thống sẽ bắt đầu ở chế độ INIT và chuyển sang AUTO sau 1 giây.