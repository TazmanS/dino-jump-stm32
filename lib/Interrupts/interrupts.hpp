#pragma once

using Callback = void (*)();

void interruptors_config();

void EXTI0_callback(Callback callback);
void EXTI1_callback(Callback callback);
