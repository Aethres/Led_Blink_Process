# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\turan\Desktop\Dev\Workspace01\Test\Led_Blink_Process.cydsn\Led_Blink_Process.cyprj
# Date: Mon, 31 Jul 2023 10:06:56 GMT
#set_units -time ns
create_clock -name {cyCapsense_ModClk(FFB)} -period 5312.5 -waveform {0 2656.25} [list [get_pins {ClockBlock/ff_div_7}]]
create_clock -name {cyCapsense_SnsClk(FFB)} -period 5312.5 -waveform {0 2656.25} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {Clock_1(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_11}]]
create_clock -name {cyUart_p50_p51_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_4}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {cyCapsense_ModClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {cyCapsense_SnsClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {cyUart_p50_p51_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\turan\Desktop\Dev\Workspace01\Test\Led_Blink_Process.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\turan\Desktop\Dev\Workspace01\Test\Led_Blink_Process.cydsn\Led_Blink_Process.cyprj
# Date: Mon, 31 Jul 2023 10:06:51 GMT
