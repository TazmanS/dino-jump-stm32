#pragma once

using Callback = void (*)();

void interruptors_config();

void EXTI4_callback(Callback callback);
void EXTI5_callback(Callback callback);
