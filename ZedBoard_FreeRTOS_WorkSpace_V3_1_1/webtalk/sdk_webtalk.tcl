webtalk_init -webtalk_dir /home/jaffe5/Projects/zedboard/ZedBoard_FreeRTOS_WorkSpace_V3_1_1/webtalk
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "Fri Mar 25 00:30:04 2016" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "SDK v2015.4" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "2015.4" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "amd64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "SDK" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "false" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "NA" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "dfn887oeprpbdbe8nkjbo6e5um" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "2015.4_2" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "2" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "" -context "user_environment"
webtalk_add_data -client project -key os_release -value "" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "" -context "user_environment"
webtalk_register_client -client sdk
webtalk_add_data -client sdk -key uid -value "1458878751000" -context "sdk\\\\application/1458878751000"
webtalk_add_data -client sdk -key hwid -value "1456502950745" -context "sdk\\\\application/1458878751000"
webtalk_add_data -client sdk -key bspid -value "1456502992389" -context "sdk\\\\application/1458878751000"
webtalk_add_data -client sdk -key newbsp -value "false" -context "sdk\\\\application/1458878751000"
webtalk_add_data -client sdk -key os -value "freertos823_xilinx" -context "sdk\\\\application/1458878751000"
webtalk_add_data -client sdk -key apptemplate -value "empty_application" -context "sdk\\\\application/1458878751000"
webtalk_transmit -clientid 3953288396 -regid "" -xml /home/jaffe5/Projects/zedboard/ZedBoard_FreeRTOS_WorkSpace_V3_1_1/webtalk/usage_statistics_ext_sdk.xml -html /home/jaffe5/Projects/zedboard/ZedBoard_FreeRTOS_WorkSpace_V3_1_1/webtalk/usage_statistics_ext_sdk.html -wdm /home/jaffe5/Projects/zedboard/ZedBoard_FreeRTOS_WorkSpace_V3_1_1/webtalk/sdk_webtalk.wdm -intro "<H3>SDK Usage Report</H3><BR>"
webtalk_terminate
