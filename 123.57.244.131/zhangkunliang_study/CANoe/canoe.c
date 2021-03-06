/*@!Encoding:936*/


includes
{
    
}


variables
{
    float x;
  
    long ackresult;
    long funrel;
    long result;
    long Logic_address_length = 2;

    int socket_count = 0;
    int count = 0;
    int TCP_DATA_PROT = 13400;
    int UDP_DISCOVERY_PROT = 13400;
    int TEST_PORT_ZERO = 13400;
    int TEST_PORT_ONE = 13401;
    int TEST_PORT_TWO = 13402;
    int isconnect = 0;
  
    char errorString[500];
    char Tmp_address[16];
    char Receive_Buffer[1500];
    char Vehicle_VIN[17];
    char Vehicle_EID[12];
    char Vehicle_GID[12];
   // char test_equipment_address[16] = "192.168.50.33";
    // char doip_stack_server_address[20] = "192.168.50.1"
  
    dword DoIP_Server_Address;
    dword Broadcast_address;
    dword source_adderss;
    dword Tester_address;
    dword udpsocket = 0;
    dword tcpsocket = 0;
    dword tcpsocket1 = 0;
    dword tcpsocket2 = 0;
    dword tcpsocket3 = 0;
    dword tcpsockettemp = 0;
  
    int A_DoIP_Ctrl = 2000;
    int A_DoIP_Announce_Wait = 500;
    int A_DoIP_Announce_Interval = 500;
    int A_DoIP_Diagnostic_Message = 2000;
    int T_TCP_Initial_Inactivity = 2000;
    int T_TCP_Alive_Check = 500;
    int A_Vehicle_Discovery_Timer = 5000;
    long T_TCP_General_Inactivity = 5 * 60 * 1000;

    byte Tester_Logic_address[2];
    byte DoIP_Logic_address[2];


    byte DoIPTest_Vehicle_Identity_Request[8] =
    {
        0x02, 0xFD, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00
    };
    byte DoIPTest_Vehicle_Identity_Response[40] =
    {
        0x02, 0xFD, 0x00, 0x04, 0x00,
        0x00, 0x00, 0x20, 0x49, 0x56,
        0x49, 0x38, 0x38, 0x41, 0x42,
        0x43, 0x44, 0x31, 0x39, 0x38,
        0x30, 0x30, 0x34, 0x31, 0x38,
        0x00, 0x03, 0x18, 0x03, 0x73,
        0xCB, 0x6B, 0x33, 0x18, 0x03,
        0x73, 0xCB, 0x6B, 0x33, 0x00
    };


    byte DoIPTest_Vehicle_Identity_Vin_Request[25] =
    {
        0x02, 0xFD, 0x00, 0x03, 0x00,
        0x00, 0x00, 0x11, 0x49, 0x56,
        0x49, 0x38, 0x38, 0x41, 0x42,
        0x43, 0x44, 0x31, 0x39, 0x38,
        0x30, 0x30, 0x34, 0x31, 0x38
    };
    byte DoIPTest_Vehicle_Identity_Vin_Response[40] =
    {
        0x02, 0xFD, 0x00, 0x04, 0x00,
        0x00, 0x00, 0x20, 0x49, 0x56,
        0x49, 0x38, 0x38, 0x41, 0x42,
        0x43, 0x44, 0x31, 0x39, 0x38,
        0x30, 0x30, 0x34, 0x31, 0x38,
        0x00, 0x03, 0x18, 0x03, 0x73,
        0xCB, 0x6B, 0x33, 0x18, 0x03,
        0x73, 0xCB, 0x6B, 0x33, 0x00
    };


    byte DoIPTest_Vehicle_Identity_Eid_Request[14] =
    {
        0x02, 0xFD, 0x00, 0x02, 0x00,
        0x00, 0x00, 0x06, 0x18, 0x03,
        0x73, 0xCB, 0x6B, 0x33
    };
    byte DoIPTest_Vehicle_Identity_Eid_Response[40] =
    {
        0x02, 0xFD, 0x00, 0x04, 0x00,
        0x00, 0x00, 0x20, 0x49, 0x56,
        0x49, 0x38, 0x38, 0x41, 0x42,
        0x43, 0x44, 0x31, 0x39, 0x38,
        0x30, 0x30, 0x34, 0x31, 0x38,
        0x00, 0x03, 0x18, 0x03, 0x73,
        0xCB, 0x6B, 0x33, 0x18, 0x03,
        0x73, 0xCB, 0x6B, 0x33, 0x00
    };


    byte DoIPTest_Vehicle_Power_Mode_Request[8] =
    {
        0x02, 0xFD, 0x40, 0x03, 0x00,
        0x00, 0x00, 0x00
    };
    byte DoIPTest_Vehicle_Power_Mode_Response[9] =
    {
        0x02, 0xFD, 0x40, 0x04, 0x00,
        0x00, 0x00, 0x01, 0x01
    };


    byte DoIPTest_Vehicle_Entity_Status_Request[8] =
    {
        0x02, 0xFD, 0x40, 0x01, 0x00,
        0x00, 0x00, 0x00
    };
    byte DoIPTest_Vehicle_Entity_Status_Response[15] =
    {
        0x02, 0xFD, 0x40, 0x02, 0x00,
        0x00, 0x00, 0x07, 0x00, 0xFF,
        0x00, 0x00, 0x1E, 0xD2, 0xA0
    };


    byte DoIPTest_Vehicle_Routing_Activation_Request[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_Response[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x10, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_00[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_01[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x01, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_02[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x02, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_03[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x03, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_04[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x04, 0x00, 0x00,
        0x00, 0x00
    };
    byte DoIPTest_Vehicle_Routing_Activation_NACK_Code_06[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x06, 0x00, 0x00,
        0x00, 0x00
    };


    byte DoIPTest_Vehicle_Diagnostic_Request[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0x00, 0x01, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_Vehicle_Diagnostic_Response[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x00, 0x01,
        0x0E, 0x01, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_Vehicle_Diagnostic_Function_Request[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0xE4, 0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_Vehicle_Diagnostic_Positive[13] =
    {
        0x02, 0xFD, 0x80, 0x02, 0x00,
        0x00, 0x00, 0x05, 0x00, 0x01,
        0x0E, 0x01, 0x00
    };
    byte DoIPTest_Vehicle_Diagnostic_Negative_Code_02[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0x00, 0x01,
        0x0E, 0x01, 0x02
    };


    byte DoIPTest_Vehicle_Alive_Check_Request[8] =
    {
        0x02, 0xFD, 0x00, 0x07, 0x00,
        0x00, 0x00, 0x00
    };
    byte DoIPTest_Vehicle_Alive_Check_Response[10] =
    {
        0x02, 0xFD, 0x00, 0x08, 0x00,
        0x00, 0x00, 0x02, 0x0E, 0x01
    };


    byte DoIPTest_Header_NACK_Code_00[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00
    };


    byte DoIPTest_Header_NACK_Code_01[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01
    };


    byte DoIPTest_Header_NACK_Code_04[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x04
    };


    byte DoIPTest_103_req[8] =
    {
        0xFF, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00
    };


    byte DoIPTest_104_req[8] =
    {
        0x01, 0xFD, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00
    };


    byte DoIPTest_105_req[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };


    byte DoIPTest_106_req[15] =
    {
        0x01, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00
    };

    byte DoIPTest_107_req[8] =
    {
        0x01, 0xFE, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00
    };


    byte DoIPTest_108_req[8] =
    {
        0x02, 0xFD, 0x11, 0x11, 0x00,
        0x00, 0x00, 0x00
    };


    byte DoIPTest_109_req[15] =
    {
        0x02, 0xFD, 0x11, 0x11, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00
    };


    byte DoIPTest_110_req[14] =
    {
        0x02, 0xFD, 0x00, 0x02, 0x00,
        0x00, 0x00, 0x05, 0x18, 0x03,
        0x73, 0xCB, 0x6B, 0x33
    };


    byte DoIPTest_204_req[14] =
    {
        0x02, 0xFD, 0x00, 0x02, 0x00,
        0x00, 0x00, 0x06, 0x18, 0x03,
        0x73, 0xBB, 0xBB, 0x33
    };


    byte DoIPTest_205_req[25] =
    {
        0x02, 0xFD, 0x00, 0x03, 0x00,
        0x00, 0x00, 0x11, 0x49, 0x56,
        0x49, 0x38, 0x38, 0x41, 0x42,
        0x43, 0x44, 0x31, 0x39, 0x38,
        0x30, 0x30, 0xDD, 0xDD, 0xDD
    };


    byte DoIPTest_303_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0D, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    byte DoIPTest_303_res[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0D, 0x00,
        0x00, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00
    };


    byte DoIPTest_305_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x02,
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    byte DoIPTest_305_res[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x02,
        0x00, 0x03, 0x01, 0x00, 0x00,
        0x00, 0x00
    };


    byte DoIPTest_307_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x02,
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    byte DoIPTest_307_res[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x02,
        0x00, 0x03, 0x02, 0x00, 0x00,
        0x00, 0x00
    };


    byte DoIPTest_311_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0xDD, 0x00, 0x00, 0x00, 0x00
    };
    byte DoIPTest_311_res[17] =
    {
        0x02, 0xFD, 0x00, 0x06, 0x00,
        0x00, 0x00, 0x09, 0x0E, 0x01,
        0x00, 0x03, 0x06, 0x00, 0x00,
        0x00, 0x00
    };


    byte DoIPTest_405_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0D, 0x00,
        0x00, 0x01, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_405_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0x00, 0x01,
        0x0D, 0x00, 0x02
    };


    byte DoIPTest_406_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0x00, 0x01,
        0x0E, 0x01, 0x06
    };


    byte DoIPTest_407_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0x01, 0x33, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_407_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0x01, 0x33,
        0x0E, 0x01, 0x03
    };


    byte DoIPTest_409_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0x01, 0x44, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_409_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0x01, 0x44,
        0x0E, 0x01, 0x03
    };


    byte DoIPTest_902_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0xE4, 0x01, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };


    byte DoIPTest_902_res[13] =
    {
        0x02, 0xFD, 0x80, 0x02, 0x00,
        0x00, 0x00, 0x05, 0x01, 0x30,
        0x0E, 0x01, 0x00
    };



    byte DoIPTest_903_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0E, 0x01,
        0xE0, 0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_903_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0xE0, 0x00,
        0x0E, 0x01, 0x03
    };


    byte DoIPTest_904_req[18] =
    {
        0x02, 0xFD, 0x80, 0x01, 0x00,
        0x00, 0x00, 0x0A, 0x0D, 0x00,
        0xE4, 0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06
    };
    byte DoIPTest_904_res[13] =
    {
        0x02, 0xFD, 0x80, 0x03, 0x00,
        0x00, 0x00, 0x05, 0xE4, 0x00,
        0x0D, 0x00, 0x02
    };

    byte DoIPTest_1101_res[15] =
    {
        0x02, 0xFD, 0x40, 0x02, 0x00,
        0x00, 0x00, 0x07, 0x01, 0xFF,
        0x00, 0x00, 0x1E, 0xD2, 0xA0
    };


    byte DoIPTest_1104_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0x00, 0x12, 0x34, 0x56, 0x78
    };

    byte DoIPTest_1106_req[15] =
    {
        0x02, 0xFD, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x07, 0x0E, 0x01,
        0x00, 0x32, 0x40, 0x00, 0x00
    };


    // ne_doip_debug_testcase>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
    byte power_mode_true[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01
    };
    byte power_mode_false[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x02
    };
    byte activation_line_true[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x03
    };
    byte activation_line_false[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x04
    };
    byte vehicle_announce[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x05
    };
    byte vehicle_announce_other_ports[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x06
    };
    byte routing_activation_auth_true[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x07
    };
    byte routing_activation_auth_false[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x08
    };
    byte entity_type_node[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x09
    };
    byte entity_type_gateway[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x0A
    };
    byte entity_type_mcts_1[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x0B
    };
    byte entity_type_mcts_255[9] =
    {
        0x02, 0xFD, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x0C
    };


}


void change_protocol_persion(byte protocol_persion, byte inverse_protocol_persion)
{

    byte zero = 0;
    byte one = 1;


    DoIPTest_Vehicle_Identity_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Identity_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Identity_Vin_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Vin_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Identity_Vin_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Vin_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Identity_Eid_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Eid_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Identity_Eid_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Identity_Eid_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Power_Mode_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Power_Mode_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Power_Mode_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Power_Mode_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Entity_Status_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Entity_Status_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Entity_Status_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Entity_Status_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_NACK_Code_00[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_NACK_Code_00[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_NACK_Code_01[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_NACK_Code_01[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_NACK_Code_02[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_NACK_Code_02[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_NACK_Code_03[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_NACK_Code_03[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Routing_Activation_NACK_Code_06[zero] = protocol_persion;
    DoIPTest_Vehicle_Routing_Activation_NACK_Code_06[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Diagnostic_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Diagnostic_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Diagnostic_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Diagnostic_Response[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Diagnostic_Function_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Diagnostic_Function_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Diagnostic_Positive[zero] = protocol_persion;
    DoIPTest_Vehicle_Diagnostic_Positive[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Diagnostic_Negative_Code_02[zero] = protocol_persion;
    DoIPTest_Vehicle_Diagnostic_Negative_Code_02[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Alive_Check_Request[zero] = protocol_persion;
    DoIPTest_Vehicle_Alive_Check_Request[one] = inverse_protocol_persion;


    DoIPTest_Vehicle_Alive_Check_Response[zero] = protocol_persion;
    DoIPTest_Vehicle_Alive_Check_Response[one] = inverse_protocol_persion;


    DoIPTest_Header_NACK_Code_00[zero] = protocol_persion;
    DoIPTest_Header_NACK_Code_00[one] = inverse_protocol_persion;


    DoIPTest_Header_NACK_Code_01[zero] = protocol_persion;
    DoIPTest_Header_NACK_Code_01[one] = inverse_protocol_persion;


    DoIPTest_Header_NACK_Code_04[zero] = protocol_persion;
    DoIPTest_Header_NACK_Code_04[one] = inverse_protocol_persion;


    DoIPTest_105_req[zero] = protocol_persion;
    DoIPTest_105_req[one] = inverse_protocol_persion;


    DoIPTest_108_req[zero] = protocol_persion;
    DoIPTest_108_req[one] = inverse_protocol_persion;


    DoIPTest_110_req[zero] = protocol_persion;
    DoIPTest_110_req[one] = inverse_protocol_persion;


    DoIPTest_204_req[zero] = protocol_persion;
    DoIPTest_204_req[one] = inverse_protocol_persion;


    DoIPTest_205_req[zero] = protocol_persion;
    DoIPTest_205_req[one] = inverse_protocol_persion;


    DoIPTest_303_req[zero] = protocol_persion;
    DoIPTest_303_req[one] = inverse_protocol_persion;


    DoIPTest_303_res[zero] = protocol_persion;
    DoIPTest_303_res[one] = inverse_protocol_persion;


    DoIPTest_305_req[zero] = protocol_persion;
    DoIPTest_305_req[one] = inverse_protocol_persion;


    DoIPTest_305_res[zero] = protocol_persion;
    DoIPTest_305_res[one] = inverse_protocol_persion;


    DoIPTest_307_req[zero] = protocol_persion;
    DoIPTest_307_req[one] = inverse_protocol_persion;


    DoIPTest_307_res[zero] = protocol_persion;
    DoIPTest_307_res[one] = inverse_protocol_persion;


    DoIPTest_311_req[zero] = protocol_persion;
    DoIPTest_311_req[one] = inverse_protocol_persion;


    DoIPTest_311_res[zero] = protocol_persion;
    DoIPTest_311_res[one] = inverse_protocol_persion;


    DoIPTest_405_req[zero] = protocol_persion;
    DoIPTest_405_req[one] = inverse_protocol_persion;


    DoIPTest_405_res[zero] = protocol_persion;
    DoIPTest_405_res[one] = inverse_protocol_persion;


    DoIPTest_406_res[zero] = protocol_persion;
    DoIPTest_406_res[one] = inverse_protocol_persion;


    DoIPTest_407_req[zero] = protocol_persion;
    DoIPTest_407_req[one] = inverse_protocol_persion;


    DoIPTest_407_res[zero] = protocol_persion;
    DoIPTest_407_res[one] = inverse_protocol_persion;


    DoIPTest_409_req[zero] = protocol_persion;
    DoIPTest_409_req[one] = inverse_protocol_persion;


    DoIPTest_409_res[zero] = protocol_persion;
    DoIPTest_409_res[one] = inverse_protocol_persion;


    DoIPTest_902_req[zero] = protocol_persion;
    DoIPTest_902_req[one] = inverse_protocol_persion;


    DoIPTest_902_res[zero] = protocol_persion;
    DoIPTest_902_res[one] = inverse_protocol_persion;


    DoIPTest_903_req[zero] = protocol_persion;
    DoIPTest_903_req[one] = inverse_protocol_persion;


    DoIPTest_903_res[zero] = protocol_persion;
    DoIPTest_903_res[one] = inverse_protocol_persion;


    DoIPTest_904_req[zero] = protocol_persion;
    DoIPTest_904_req[one] = inverse_protocol_persion;


    DoIPTest_904_res[zero] = protocol_persion;
    DoIPTest_904_res[one] = inverse_protocol_persion;

}


// UDP connection
void Udp_On(dword port)
{

    get_dut_broadcast_address();
    get_dut_server_address();
    get_tester_address();

    udpsocket = UdpOpen(Tester_address, port);
    if (udpsocket != ~0) {

        TestStep("", "Udpopen: socket create Successful with socket is %d", udpsocket);
    }
    else{

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Udpopen: socket create failed with result %d (%s)", IpGetLastError(), errorString);
    }

    TestStep ("", "Udp_On:udpsocket = [%d] source_port = [%d]", udpsocket, port);

}


// UDP OFF
void Udp_Off()
{

    funrel = UdpClose(udpsocket);
    if (funrel == 0) {

        TestStep ("", "UdpClose: socket close Successful");
    }
    else if (funrel == -1) {
        funrel = IpGetLastSocketError(udpsocket);
        if (funrel != 997) {

            IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
            TestStepWarning ("", "UdpClose: socket close failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
        }
    }
    else {

        TestStep("", "UdpClose:  socket close failed  failed with result %d", funrel);
    }

}

on ethernetPacket *
{
    int count;
    if(this.doip.IsAvailable()) {

        count = this.doip.byteOffset;
        if (this.byte(count) + this.byte(count+1)  == 0xFF ) { // protocol version    
            if (this.byte(count+2)  == 0x00 && this.byte(count+3)  == 0x04) { // Vehicle announcement message/vehicle identification response
                
                testSupplyTextEvent("DoIP_vehicle_identity_response");
            }
        }
    }
}   


// UDP callback function
void OnUdpReceiveFrom(dword socket, long result1, dword address, dword port, byte buffer[], dword size)
{
  testStep("","doip callback");
    if (result1 == 0) {
        //doip
        if (buffer[0] + buffer[1] == 0xFF ) { // protocol version
            
            if (buffer[2] == 0x00 && buffer[3] == 0x04) { // Vehicle announcement message/vehicle identification response
                
                if (!memcmp(DoIPTest_Vehicle_Identity_Response, buffer, size)) {
                    write("buffer is ");
                    testSupplyTextEvent("DoIP_vehicle_identity_response");
                }

            }
            else if (buffer[2] == 0x40 && buffer[3] == 0x02) { // DoIP entity status response

                if (!memcmp(DoIPTest_Vehicle_Entity_Status_Response, buffer, size)) {

                    testSupplyTextEvent("DoIP_vehicle_entity_status_response");
                }
                else if (!memcmp(DoIPTest_1101_res, buffer, size)) {
                    testSupplyTextEvent("DoIP_vehicle_entity_status_response");
                }

            }
            else if (buffer[2] == 0x40 && buffer[3] == 0x04) { // DOIP entity power mode information response

                if (!memcmp(DoIPTest_Vehicle_Power_Mode_Response, buffer, size)) {

                    testSupplyTextEvent("DoIP_vehicle_power_mode_response");
                }

            }
            else if (buffer[2] == 0x00 && buffer[3] == 0x00) { // Generic DoIP header negative acknowledge

                if (!memcmp(DoIPTest_Header_NACK_Code_00, buffer, size)) {

                    testSupplyTextEvent("DoIP_header_resolution_failure_code_00");
                }
                else if (!memcmp(DoIPTest_Header_NACK_Code_01, buffer, size)) {

                    testSupplyTextEvent("DoIP_header_resolution_failure_code_01");
                }
                else if (!memcmp(DoIPTest_Header_NACK_Code_04, buffer, size)) {

                    testSupplyTextEvent("DoIP_header_resolution_failure_code_04");
                }
                else if (!memcmp(power_mode_false, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_power_mode");
                }
                else if (!memcmp(entity_type_node, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_entity_status");
                }
                else if (!memcmp(routing_activation_auth_true, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_routing_activation_auth");
                }
                else if (!memcmp(routing_activation_auth_false, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_routing_activation_not_auth");
                }
                else if (!memcmp(entity_type_mcts_1, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_entity_status_mcts_1");
                }
                else if (!memcmp(entity_type_mcts_255, buffer, size)) {

                    testSupplyTextEvent("DoIP_debug_doip_entity_status_mcts_255");
                }



            }
             
        }
        else {
            
            TestStepFail("", "protocol version not is doip");
        }
    }

    udprec();
}


void OnTcpConnect(dword socket, long result)
{  
  
    teststep("", "tcp socket create is successful");
    if (result == 0) {
        // start receiving on socket using TcpReceive
        isconnect = 1;
    }
    else {

        isconnect = 2;
    }
}


//TCP connection/TCP ON
dword TCPon(dword port) //source port
{
    get_dut_broadcast_address();
    get_dut_server_address();
    get_tester_address();

    tcpsockettemp = TcpOpen(Tester_address, port);

    if (tcpsockettemp != ~0) {

        TestStep("", "TcpOpen: socket create Successful with socket is %d", tcpsockettemp);
        funrel = TcpConnect(tcpsockettemp, DoIP_Server_Address, TCP_DATA_PROT);
        if (funrel != 0 && ipGetLastSocketError(tcpsockettemp) != 10035 ) {

            IpGetLastSocketErrorAsString(tcpsockettemp, errorString, elcount(errorString) );
            TestStepFail("", "TcpConnect: TCP connection failed, %s (Result %d)", errorString, IpGetLastSocketError(tcpsockettemp));
        }
        else {

            TestStep  ("", "TcpConnect: TCP connection Successful");
            
        }
    }
    else {

        IpGetLastSocketErrorAsString(tcpsockettemp, errorString, elcount(errorString));
        TestStepFail("", "TcpOpen: socket create failed with result %d (%s)", IpGetLastError(), errorString);
    }

    TestStep ("", "TCPon: tcpsocket = [%d] source_port = [%d] target_port = [%d]", tcpsockettemp, port, TCP_DATA_PROT);

    TestWaitForTimeout(500);
    return tcpsockettemp;
}


//TCP OFF
void TCPoff(dword tcpsocket)
{

    funrel = TcpClose(tcpsocket);
    if (funrel == 0) {

        TestStep ("", "TcpClose: TCP close Successful");
    }
    else if (funrel == -1) {
        funrel = IpGetLastSocketError(tcpsocket);
        if (funrel != 997) {

            IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
            TestStep ("", "TcpClose: TCP close failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
        }
    }
    else {

        TestStep("", "TcpClose:  TCP close  failed with result %d", funrel);
    }
    
}


// Set receive buffer
void tcprec(dword tcpsocket)
{
    funrel = TcpReceive(tcpsocket, Receive_Buffer, elcount(Receive_Buffer)); 
}


// Set receive buffer
void udprec()
{
    funrel = UdpReceiveFrom(udpsocket, Receive_Buffer, elcount(Receive_Buffer));
}


void OnTcpClose(dword socket, long result)
{
    tcpclose(tcpsocket);
    tcpclose(tcpsocket1);
}


//TCP callback function
void OnTcpReceive(dword tcpsocket, long result1, dword address, dword port, byte buffer[], dword size)
{
    if (result1 == 0) {

        if (size == 0) {
            TestStep ("", "OnTcpReceive: socket closed by peer");
        }
        else {
            if (buffer[0] + buffer[1] == 0xFF) { // protocol version

                if (buffer[2] == 0x00 && buffer[3] == 0x06) { // Routing activation response

                    if (!memcmp(DoIPTest_Vehicle_Routing_Activation_Response, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_response");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_00, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_00");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_01, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_01");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_02, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_02");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_03, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_03");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_06, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_06");
                    }
                    else if (!memcmp(DoIPTest_303_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_00");
                    }
                    else if (!memcmp(DoIPTest_305_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_01");
                    }
                    else if (!memcmp(DoIPTest_307_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_02");
                    }
                    else if (!memcmp(DoIPTest_311_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_06");
                    }
                    else if (!memcmp(DoIPTest_Vehicle_Routing_Activation_NACK_Code_04, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_routing_activation_NACK_code_04");
                    }


                }
                else if (buffer[2] == 0x80 && buffer[3] == 0x03) { // Diagnostic message negative acknowledgement

                    if (!memcmp(DoIPTest_405_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_02");
                    }
                    else if (!memcmp(DoIPTest_407_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_03");
                    }
                    else if (!memcmp(DoIPTest_409_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_03");
                    }
                    else if (!memcmp(DoIPTest_903_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_03");
                    }
                    else if (!memcmp(DoIPTest_904_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_02");
                    }
                    else if (!memcmp(DoIPTest_406_res, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_negative_code_06");
                    }    

                }
                else if (buffer[2] == 0x80 && buffer[3] == 0x02) { // Diagnostic message positive acknowledgement

                    if ((!memcmp(DoIPTest_Vehicle_Diagnostic_Positive, buffer, size)) || (!memcmp(DoIPTest_902_res, buffer, size))) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_positive_response");
                    }


                }
                else if (buffer[2] == 0x80 && buffer[3] == 0x01) { // Diagnostic message response

                    if (!memcmp(DoIPTest_Vehicle_Diagnostic_Response, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_diagnostic_message_response");
                    }

                }
                else if (buffer[2] == 0x00 && buffer[3] == 0x08) { // alive check message response

                    if (!memcmp(DoIPTest_Vehicle_Alive_Check_Response, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_alive_check_response");
                    }


                }
                else if (buffer[2] == 0x00 && buffer[3] == 0x07) { // alive check message request
                  
                    if (!memcmp(DoIPTest_Vehicle_Alive_Check_Request, buffer, size)) {

                        testSupplyTextEvent("DoIP_vehicle_alive_check_request");
                    }
                }
                else if (buffer[2] == 0x00 && buffer[3] == 0x00) { // header negative acknowledge

                    if (!memcmp(DoIPTest_Header_NACK_Code_00, buffer, size)) {

                        testSupplyTextEvent("DoIP_header_resolution_failure_code_00");
                    }
                    else if (!memcmp(DoIPTest_Header_NACK_Code_01, buffer, size)) {

                        testSupplyTextEvent("DoIP_header_resolution_failure_code_01");
                    }
                    else if (!memcmp(DoIPTest_Header_NACK_Code_04, buffer, size)) {

                        testSupplyTextEvent("DoIP_header_resolution_failure_code_04");
                    }

                }
                
            }
        }
    }
    
    TestStep ("", "OnTcpReceive: socket closed by peer");
    tcprec(tcpsocket);

}


testcase DoIPTest_001()
{

    TestCaseTitle("TCP_UDP", "DoIPTest_001");
    TestCaseDescription("[Description] Verify The TCP connection connects on port TCP_DATA[13400].\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,TCP TCP_DATA_PROT = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    if (isconnect == 1) {

        TestStepPass("", "DoIPTest_001 is successful with OnTcpConnect return true code %d", isconnect);
    }
    else if (isconnect == 2) {

        TestStepFail("", "DoIPTest_001 is failed with OnTcpConnect return false code %d", isconnect);
    }
    else {

        TestStepFail("", "OnTcpConnect is no call");
    }

    TCPoff(tcpsocket);
    isconnect = 0;
    TestWaitForTimeout(1000);

}


testcase DoIPTest_002()
{
    
    TestCaseTitle("TCP_UDP", "DoIPTest_002");
    TestCaseDescription("[Description] TCP connections cannot be connected on ports other than TCP_DATA[13400].\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,TCP TCP_DATA_PROT = 13401.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13401", "int");

    TestWaitForTimeout(100);
    TCP_DATA_PROT = 13401;

    tcpsocket = TCPon(TEST_PORT_ONE);
    if(isconnect == 0) {

        TestStepFail("", "DoIPTest_002 is failed");
    }
    else if(isconnect == 1) {
        
        TestStepPass("", "DoIPTest_002 is successful with OnTcpConnect false code %d", isconnect);
    }
    else {

        TestStepPass("", "DoIPTest_002 is successful with OnTcpConnect false code %d", isconnect);
    }

    TCP_DATA_PROT = 13400;
    TCPoff(tcpsocket);
    isconnect = 0;
    TestWaitForTimeout(1000);

}


testcase DoIPTest_003()
{

    TestCaseTitle("TCP_UDP","DoIPTest_003");
    TestCaseDescription("[Description] Verify that each DoIP entity should support TCP data socket, where is the number of concurrent TCP data connections supported by the respective DoIP entities.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,_DES_PORT = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("SRC_PORT", "13400", "int");
    TestCaseReportMeasuredValue("SRC_PORT", "13401", "int");
    TestCaseReportMeasuredValue("SRC_PORT", "13402", "int");

    // one

    tcpsocket = TCPon(TEST_PORT_ZERO);
    if (isconnect == 1) {

        socket_count++;
        TestStepPass("", "DoIPTest_003 socket1 is successful with OnTcpConnect return true code %d", isconnect);
    }
    else if (isconnect == 2) {

        TestStepFail("", "DoIPTest_003 socket1 is failed with OnTcpConnect return false code %d", isconnect);
    }
    else {

        TestStepFail("", "OnTcpConnect is no call");    
    }
    TestWaitForTimeout(1000);

    // two
    isconnect = 0;
    tcpsocket1 = TCPon(TEST_PORT_ONE);
    if (isconnect == 1) {
        
        socket_count++;
        TestStepPass("", "DoIPTest_003 socket2 is successful with OnTcpConnect return true code %d", isconnect);
    }
    else if (isconnect == 2) {
        
        TestStepFail("", "DoIPTest_003 socket2 is failed with OnTcpConnect return false code %d", isconnect);
    }
    else {
        TestStepFail("", "OnTcpConnect is no call");
        
    }
    TestWaitForTimeout(1000);

    // three
    isconnect = 0;
    tcpsocket2 = TCPon(TEST_PORT_TWO);
    if (isconnect == 1) {

        socket_count++;
        TestStepPass("", "DoIPTest_003 socket3 is successful with OnTcpConnect return true code %d", isconnect);
    }
    else if (isconnect == 2) {
        
        TestStepFail("", "DoIPTest_003 socket3 is failed with OnTcpConnect return false code %d", isconnect);
    }
    else {

        TestStepFail("", "OnTcpConnect is no call"); 
    }

    if (socket_count == 3) {

        TestStepPass("", "DoIPTest_003 is successful");
    }
    else {

        TestStepFail("", "DoIPTest_003 is failed");
    }

    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    TCPoff(tcpsocket1);
    TestWaitForTimeout(1000);
    TCPoff(tcpsocket2);
    TestWaitForTimeout(1000);

    isconnect = 0;

}


testcase DoIPTest_004()
{

    TestCaseTitle("TCP_UDP", "DoIPTest_004");
    TestCaseDescription("[Description] UDP connections are connected on the target port UDP_DISCOVERY[13400] and source port UDP_TEST_EQUIPMENT_REQUEST[dynamically assigned].\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,IP = 1255.255.255.255");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD_TYPE", "0x0001", "int");

    Udp_On(0);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50); // 50ms:network delay
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_004 is successful with receive true response");
    }
    else {

        TestStepFail("", "DoIPTest_004 is failed with receive false response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_005()
{

    TestCaseTitle("TCP_UDP", "DoIPTest_005");
    TestCaseDescription("[Description] UDP connections cannot connect on target port not for UDP_DISCOVERY[13400] and source port for UDP_TEST_EQUIPMENT_REQUEST[dynamically assigned].\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD. 3,UDP PROT = 13401.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13401", "int");
    TestCaseReportMeasuredValue("PAYLOAD_TYPE", "0001", "int");

    Udp_On(0);
    funrel = UdpSendTo(udpsocket, Broadcast_address, TEST_PORT_ONE, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50); // 50ms:network delay
    if (funrel == 1) {

        TestStepFail("", "DoIPTest_005 is failed with receive vehicle identity response");
    }
    else {

        TestStepPass("", "DoIPTest_005 is successful with not receive response");
    }

    Udp_Off();
    TestWaitForTimeout(1000);

}


// Network options need to be set
testcase DoIPTest_101()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_101");
    TestCaseDescription("[Description] Any packets with a  broadcast address as the source IP address shall be ignored.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.33  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.33", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    TestStep ("", "Udp_On: source_IP = [%s]  source_port = [%d]", "192.168.50.33", UDP_DISCOVERY_PROT);
    TestStep ("", "UdpSendTo: target_IP = [%s]  target_port = [%d]", "192.168.50.33", UDP_DISCOVERY_PROT);
    TestStepPass("", "DoIPTest_101 is successful with not receive udp request message");
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_102()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_102");
    TestCaseDescription("[Description] Verify the supported protocol version.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,IP = 255.255.255.255  4,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("Protocol Version", "0x02", "int");
    TestCaseReportMeasuredValue("Inverse Protocol Version", "0x0FD", "int");

    
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {
        TestStepFail("", "Send vehicle identity message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);//50ms network delay
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_102 is successful with support protocol version 0x02FD");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_102 response");
    }

    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_103()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_103");
    TestCaseDescription("[Description] Verify that each DoIP entity should support the default protocol version of the vehicle identification request message req = 0xFF00000100000000.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0xFF  2,Inverse protocol version = 0x00  3,IP = 255.255.255.255  4,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("Protocol Version", "0xFF", "int");
    TestCaseReportMeasuredValue("Inverse Protocol Version", "0x00", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_103_req, elcount(DoIPTest_103_req));
    if (funrel == 0)
    {
        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_103 103 is successful, vehicle discovery response received");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_103 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_104()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_104");
    TestCaseDescription("[Description] DoIP sends a negative confirmation message when the Protocol version does not match the Iinverse protocol version (Vehicle discovery UDP)  3,vehicle_identity req = 0x01FD000100000000  4,res =0x02FD00000000000100.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x01  2,Inverse protocol version = 0xFD  3,IP = 255.255.255.255  4,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("Protocol Version", "0x01", "int");
    TestCaseReportMeasuredValue("Inverse Protocol Version", "0xFD", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_104_req, elcount(DoIPTest_104_req));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_00", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_104 is successful and received response with protocol version mismatch");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_104 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);
}


testcase DoIPTest_105()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_105");
    TestCaseDescription("[Description] Verify that each DoIP entity should ignore the received generic DoIP header denial confirmation message.  3, req = Send vehicle identity request message.\n ");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02.  2,Inverse protocol version = 0xFD. 3,IP = 255.255.255.255. 4,Port = 13400.   ");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x0000", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_105_req, elcount(DoIPTest_105_req));
    if (funrel == 0) {

        TestStep ("", "Send Error payload type request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send Error payload type request message message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail(""," Send Error payload type request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIPTest_105", A_DoIP_Ctrl + 50); // 50ms network delay
    if (funrel == 1) {

        TestStepFail("", "Receive  DoIPTest_105 response");
    }
    else {

        TestStepPass("", "DoIPTest_105 is successful doip server is ignored Error payload type");
    }

    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_106()
{
    
    TestCaseTitle("Protocol header resolution", "DoIPTest_106");
    TestCaseDescription("[Description] DoIP sends a negative confirmation message when the Protocol version does not match the Iinverse protocol version (Routing activation TCP).\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x01.  2,Inverse protocol version = 0xFD  3,IP = 192.168.50.1  4,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_106_req, elCount(DoIPTest_106_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_00", A_DoIP_Ctrl + 50);
    if (funrel == 1) {
        
        TestStepPass("", "DoIPTest_106 is successful and received protocol version mismatch response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_106 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


testcase DoIPTest_107()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_107");
    TestCaseDescription("[Description] Each DoIP entity should send a generic DoIP header denial confirmation message and set the NACK code to 0x00 (vehicle discover UDP), when the DoIP entity does not support the payload type  req = 0x01FE000100000000  res =0x02FD00000000000100.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255. 2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int"); 
    TestCaseReportMeasuredValue("Protocol Version", "0x01", "int");
    TestCaseReportMeasuredValue("Inverse Protocol Version", "0xFE", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_107_req, elcount(DoIPTest_107_req));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d",funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_00" , A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_107 is successful and received protocol version mismatch response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_107 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_108()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_108");
    TestCaseDescription("[Description] Verify that the doip entity receives an invalid payload type that should respond to the associated error code(UDP vehicle identity)\n");
    TestCaseDescription("[Parameters] 1,payload type = 0x1111  2,IP = 255.255.255.255  3.Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x1111", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_108_req, elcount(DoIPTest_108_req));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d",funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_01", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_108 is successful and received payload type mismatch response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_108 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_109()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_109");
    TestCaseDescription("[Description] Each DoIP entity should send a generic DoIP header denial confirmation message and set the NACK code to 0x01 (Routing activation TCP), when the DoIP entity does not support the payload type.\n");
    TestCaseDescription("[Parameters] 1,payload type = 0x1111  2,IP = 192.168.50.1  3.Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x1111", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_109_req, elCount(DoIPTest_109_req));
    if (funrel == 0) {

        TestStep ("", "send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_01", A_DoIP_Diagnostic_Message + 50);

    if (funrel == 1) {

        TestStepPass("", "DoIPTest_109 is successful and received payload type mismatch response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_109 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
}


testcase DoIPTest_110()
{

    TestCaseTitle("Protocol header resolution", "DoIPTest_110");
    TestCaseDescription("[Description] Verify what code the doip entity responds to if the payload length does not match the actual length.\n");
    TestCaseDescription("[Parameters] 1,payload type = 0x1111  2,IP = 255.255.255.255  3.Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x1111", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_110_req, elcount(DoIPTest_110_req));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by eid Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by eid failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by eid failed with result %d",funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_04", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_110 is successful and received invalid payload length response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_110 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_111()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_111");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle discovery payload type 0x0001.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message is successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepPass("", "DoIPTest_111 is successful with receive true vehicle identity response payload type 0x0001 is support");
    }
    else{

        TestStepFail("", "Do not Receive DoIPTest_111 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}

testcase DoIPTest_112()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_112");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle discovery payload type 0x0002.\n ");
    TestCaseDescription("[Parameters] 1,IP: 255.255.255.255  2,Port = 13400  3,EID = 180373CB6B33.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Eid_Request, elcount(DoIPTest_Vehicle_Identity_Eid_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by eid is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by eid is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by eid is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_112 is successful with receive vehicle identity response payload type 0x0002 is support");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_112 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000); 
}


testcase DoIPTest_113()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_113");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle discovery payload type 0x0003.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400  3,VIN = IVI88ABCD19800418");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Vin_Request, elcount(DoIPTest_Vehicle_Identity_Vin_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by vin is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepPass("", "DoIPTest_113 is successful with receive vehicle identity response payload type 0x0003 is support");
    }
    else {

        TestStepFail("","Do not Receive DoIPTest_113 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_114()
{
    
    TestCaseTitle("Diagnostic power mode", "DoIPTest_114");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle power mode payload type 0x4003\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Power_Mode_Request, elcount(DoIPTest_Vehicle_Power_Mode_Request));
    if (funrel == 0) {

        TestStep("", "Send vehicle power mode message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle power mode message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {

        TestStepFail("", "Send vehicle power mode message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_power_mode_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_114 is successful with receive true vehicle power message mode response");
    }
    else {

        TestStepFail("", "DoIPTest_114 is failed with do not Receive vehicle power mode message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}



testcase DoIPTest_115()
{
    
    TestCaseTitle("DoIP entity status", "DoIPTest_115");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle doip entity status payload type 0x4001.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Entity_Status_Request, elcount(DoIPTest_Vehicle_Entity_Status_Request));
    if (funrel == 0) {

        TestStep ("", "Send doip entity status message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity status message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity status message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_entity_status_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_115 successful　and Receive true Send doip entity status message response");
    }
    else {

        TestStepFail("", "Do not Receive Send doip entity status message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_116()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_116");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified route activation payload type 0x0005.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {
        TestStep (""," send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", " send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail(""," send route activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("","DoIPTest_116 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("","Do not Receive DoIPTest_116 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
}


testcase DoIPTest_117()
{    

    TestCaseTitle("Diagnostic", "DoIPTest_117");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified diagnostic information payload type 0x8001.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStepPass("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_117 is successful with diagnostic response data has the same address");
    }
    else {
        TestStepFail("", "DoIPTest_117 is failed with The diagnostic response data has the different address");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_201()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_201");
    TestCaseDescription("[Description] Verify that each doip entry should support the specified vehicle information request.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message is successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepPass("", "DoIPTest_201 is successful with receive true vehicle identity response");
    }
    else{

        TestStepFail("", "Do not Receive DoIPTest_201 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_202()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_202");
    TestCaseDescription("[Description] Verify that each DoIP entity supports vehicle request messages with EID parameters.\n ");
    TestCaseDescription("[Parameters] 1,IP: 192.168.50.1  2,Port = 13400  3,EID = 180373CB6B33.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Eid_Request, elcount(DoIPTest_Vehicle_Identity_Eid_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by eid is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by eid is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by eid is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response" , A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_202 is successful and receive vehicle identity response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_202 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000); 
}


testcase DoIPTest_203()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_203");
    TestCaseDescription("[Description] Verify that each DoIP entity supports vehicle request messages with VIN parameters.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400  3,VIN = IVI88ABCD19800418");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Vin_Request, elcount(DoIPTest_Vehicle_Identity_Vin_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by vin is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepPass("", "DoIPTest_203 is successful and receive vehicle identity response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_203 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_204()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_204");
    TestCaseDescription("[Description] Verify that DoIP entities ignore vehicle requests that receive incorrect EID parameters.\n ");
    TestCaseDescription("[Parameters] 1,IP: 255.255.255.255  2,Port = 13400  3,EID = C1D2E3F4A5B6.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_204_req, elcount(DoIPTest_204_req));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message  by eid is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message  by eid is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message  by eid is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response" , A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepFail("", "Do not Receive DoIPTest_204 response");
    }
    else {

        TestStepPass("", "DoIPTest_204 is successful and not receive vehicle identity response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_205()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_205");
    TestCaseDescription("[Description] Verify that DoIP entities ignore vehicle requests that receive incorrect VIN parameters.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400  3,VIN = IVI88ABCD198904BB");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_205_req, elcount(DoIPTest_205_req));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message by vin is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message by vin is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepFail("", "Do not Receive DoIPTest_205 response");
    }
    else {

        TestStepPass("", "DoIPTest_205 is successful and not receive vehicle identity response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);
}


testcase DoIPTest_206()
{
    
    TestCaseTitle("Vehicle identification", "DoIPTest_206");
    TestCaseDescription("[Description] Verify that the response time of vehicle discovery request information is within 500ms.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("TIMEOUT", "500ms", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString( udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message is failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message is failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) { 

        TestStepPass("", "DoIPTest_206 is successful and receive vehicle identity response within 500ms");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_206 response");
    }
    
    Udp_Off();
    TestWaitForTimeout(1000);
}


testcase DoIPTest_301()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_301");
    TestCaseDescription("[Description] Verify that the routing activation request message data structure for each DoIP entity conforms to the specification routing_activation.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_301 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_301 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


testcase DoIPTest_302()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_302");
    TestCaseDescription("[Description] Verify that the logical address of the request is consistent with the logical address of the external test device that responded.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent( "DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {
        
        TestStepPass("", "DoIPTest_302 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_302 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}



// 303 is related to 304 
testcase DoIPTest_303()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_303");
    TestCaseDescription("[Description] Each DoIP entity shall send the routing activation response message with the response code set to 0x00 after having received a routing activation request message if the source address in the request message is unknown.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0D00");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_303_req, elCount(DoIPTest_303_req));
    if (funrel == 0) {

        TestStep("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_00", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_303 is successful with reveive NACK code");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_303 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


// 303 is related to 304
testcase DoIPTest_304()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_304");
    TestCaseDescription("[Description] Verify that the socket closes after receiving a response to route activation 0x00. \n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400. ");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // SA with wrong sending source address 
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_303_req, elCount (DoIPTest_303_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_00", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {
        
        TestStep ("", "Receive true DoIPTest_304 NACK code 0x00");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_304 response");
    }
    TestWaitForTimeout(1000);


    // send failed
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep (""," Send routing activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_304 is successful Send routing activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepPass("", "DoIPTest_304 is successful Send routing activation request Message failed with result %d", funrel);
    }
     
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


// 305 is related to 306
testcase DoIPTest_305()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_305");
    TestCaseDescription("[Description] Verify doip entity route activation response error code 01\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,ADDRESS = OEO1");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    // send doip stack debug testcase message
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_mcts_1, elcount(entity_type_mcts_1));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_entity_status_mcts_1", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }
    TestWaitForTimeout(1000);


    // 0E01 route activation
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", T_TCP_Initial_Inactivity + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_305 response");
    }
    TestWaitForTimeout(1000);


    // 0E02 route activation
    tcpsocket1 = TCPon(TEST_PORT_ONE);
    funrel = TcpSend(tcpsocket1, DoIPTest_305_req, elCount(DoIPTest_305_req));
    if (funrel == 0) {

        TestStep("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }
    
    
    // Receive doip entity alive check request
    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_alive_check_request", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {
        
        TestStepPass("", "Receive doip entity alive check request message");
        funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
      
    }
    else {

        TestStepFail("", "Receive doip entity alive check request message");
    }
    

    tcprec(tcpsocket1);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_01", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_305 is successful and receive routing activation message NACK code 0x01");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_305 response");
    }


    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    TCPoff(tcpsocket1);
    TestWaitForTimeout(1000);


    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_mcts_255, elcount(entity_type_mcts_255));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_entity_status_mcts_255", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }
    TestWaitForTimeout(1000);


    Udp_Off();
    TestWaitForTimeout(1000);
}


// 305 is related to 306
testcase DoIPTest_306()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_306");
    TestCaseDescription("[Description] After verifying the doip entity route activation response error code 01, the socket connection should be disconnected\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,ADDRESS = OEO1");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    // send doip stack debug testcase message
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_mcts_1, elcount(entity_type_mcts_1));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_entity_status_mcts_1", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }
    TestWaitForTimeout(1000);


    // 0E01 route activation
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_306 response");
    }
    TestWaitForTimeout(1000);


    // 0E02 route activation
    tcpsocket1 = TCPon(TEST_PORT_ONE);
    funrel = TcpSend(tcpsocket1, DoIPTest_305_req, elCount(DoIPTest_305_req));
    if (funrel == 0) {

        TestStep("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message  failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    // Receive doip entity alive check request
    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_alive_check_request", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {
        
        TestStepPass("", "Receive doip entity alive check request message");
        funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
      
    }
    else {

        TestStepFail("", "Receive doip entity alive check request message");
    }
    
    
    tcprec(tcpsocket1);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_01", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_306 is successful and receive routing activation message NACK code 0x01");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_306 response");
    }

    TestWaitForTimeout(1000);
    // send message
    funrel = TcpSend(tcpsocket1, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStepFail("", "Send route activation request Message  Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_306 is successful send route activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepPass("", "DoIPTest_306 is successful send route activation request message failed with result %d", funrel);
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    TCPoff(tcpsocket1);
    TestWaitForTimeout(1000);

    //
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_mcts_255, elcount(entity_type_mcts_255));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_entity_status_mcts_255", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }
    TestWaitForTimeout(1000);

    Udp_Off();
    TestWaitForTimeout(1000);
    
}



// 307 is related to 308 
testcase DoIPTest_307()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_307");
    TestCaseDescription("[Description] Verify doip entity route activation response error code 02.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01  4,0x0E02");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // send route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive route activation response message");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_307 response");
    }
    

    // Send route activation request on the same socket using 0X0E02
    funrel = TcpSend(tcpsocket, DoIPTest_307_req, elCount(DoIPTest_307_req));
    if (funrel == 0) {

        TestStep("", "Send SA = 0x0E02 route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_02", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_307 is successful with receive route activation response message error is 0x02");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_307 response");
    }


    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


// 307 is related to 308 
testcase DoIPTest_308()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_308");
    TestCaseDescription("[Description] Verify that the doip entity should disconnect the socket when the route activation receives error code 0x02.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // send route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive route activation response message");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_308 response");
    }
    

    // Send route activation request on the same socket using 0X0E02
    funrel = TcpSend(tcpsocket, DoIPTest_307_req, elCount(DoIPTest_307_req));
    if (funrel == 0) {

        TestStep("", "Send SA = 0x0E02 route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_02", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive route activation response message error is 0x02");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_308 response");
    }

    TestWaitForTimeout(5000);
    // Successfully sent a message to be successful
    funrel = TcpSend(tcpsocket, DoIPTest_307_req, elCount(DoIPTest_307_req));
    funrel = TcpSend(tcpsocket, DoIPTest_307_req, elCount(DoIPTest_307_req));
    if (funrel == 0) {

        TestStepFail("", "Send request message is successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_308 is successful with the message failed to be sent, and the socket connection has been disconnected. %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepPass("", "DoIPTest_308 is successful with the message failed to be sent, and the socket connection has been disconnected. %d", funrel);
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}




// 309 is related to 310 
testcase DoIPTest_309()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_309");
    TestCaseDescription("[Description] Verify doip entity route activation response error code 03.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01  4,0x0E02");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // send route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive route activation response message");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_309 response");
    }
    TestWaitForTimeout(1000);


    // Send a route activation request using 0X0E01 on the new socket connection.
    tcpsocket1 = TCPon(TEST_PORT_ONE);
    funrel = TcpSend(tcpsocket1, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send SA = 0x0E01 route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }
    
    // Receive doip entity alive check request
    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_alive_check_request", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {
        
        TestStepPass("", "Receive doip entity alive check request message");
        funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
      
    }
    else {

        TestStepFail("", "Receive doip entity alive check request message");
    }
    
    
    tcprec(tcpsocket1);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_03", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_309 is successful with receive route activation response message error is 0x03");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_309 response");
    }


    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    TCPoff(tcpsocket1);
    TestWaitForTimeout(1000);
    
}


// 309 is related to 310 
testcase DoIPTest_310()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_310");
    TestCaseDescription("[Description] Verify that the doip entity should disconnect the socket when the route activation receives error code 0x03.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // send route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive route activation response message");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_307 response");
    }
    TestWaitForTimeout(1000);


    // Send a route activation request using 0X0E01 on the new socket connection.
    tcpsocket1 = TCPon(TEST_PORT_ONE);
    funrel = TcpSend(tcpsocket1, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send SA = 0x0E01 route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepFail("", "Send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    // Receive doip entity alive check request
    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_alive_check_request", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {
        
        TestStepPass("", "Receive doip entity alive check request message");
        funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
      
    }
    else {

        TestStepFail("", "Receive doip entity alive check request message");
    }
    
    tcprec(tcpsocket1);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_03", A_Vehicle_Discovery_Timer + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_310 is successful with receive route activation response message error is 0x03");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_310 response");
    }


    TestWaitForTimeout(1000);
    // 
    funrel = TcpSend(tcpsocket1, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStepFail("", "Send SA = 0x0E01 route activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket1) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket1, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_310 is successful with send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket1), errorString );
    }
    else {

        TestStepPass("", "DoIPTest_310 is successful with send route activation request Message failed with result %d", funrel);
    }


    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    TCPoff(tcpsocket1);
    TestWaitForTimeout(1000);

}


// 311 is related to 312 
testcase DoIPTest_311()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_311");
    TestCaseDescription("[Description] Verify doip entity route activation response error code 06.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_311_req, elCount(DoIPTest_311_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_06", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_311 is successful with receive routing activation message response error code 0x06");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_311 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


// 311 is related to 312 
testcase DoIPTest_312()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_312");
    TestCaseDescription("[Description] Verify that the doip entity should disconnect the socket when the route activation receives error code 0x03.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0xDD", "int");


    // send route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_311_req, elCount(DoIPTest_311_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_06", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_312 is successful with receive routing activation message response error code 0x06");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_312 response");
    }
    

    // send message
    TestWaitForTimeout(1000);
    funrel = TcpSend(tcpsocket, DoIPTest_311_req, elCount(DoIPTest_311_req));
    TestWaitForTimeout(1000);
    funrel = TcpSend(tcpsocket, DoIPTest_311_req, elCount(DoIPTest_311_req));
    if (funrel == 0) {

        TestStepFail ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_312 is successful with send route activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepPass("", "DoIPTest_312 is successful with send route activation request Message failed with result %d", funrel);
    }


    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


testcase DoIPTest_313()
{
    
    TestCaseTitle("Routing activation", "DoIPTest_313");
    TestCaseDescription("[Description] If the SA in the Route Activation Request message has been assigned to the TCP_DATA socket receiving the request, the requested DoIP entity shall accept the route activation.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Address = 0x0E01");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    // first route activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_313 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_313 response");
    }
    

    // second route activation request message
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_313 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_313 response");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}



testcase DoIPTest_401()
{

    TestCaseTitle("Diagnostic", "DoIPTest_401");
    TestCaseDescription("[Description] Verify that each doip entity should support the diagnostic request protocol header structure.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_message_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_401 is successful with diagnostic response data has the same address");
    }
    else {
        TestStepFail("", "DoIPTest_401 is failed with The diagnostic response data has the different address");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}



testcase DoIPTest_402()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_402");
    TestCaseDescription("[Description] Verify that each doip entity should respond to diagnostic requests.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_402 is successful with diagnostic response data has the same address");
    }
    else {
        TestStepFail("", "DoIPTest_402 is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_403()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_403");
    TestCaseDescription("[Description] Verify that the response of each doip entity to the diagnostic request should be within 2S.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_403 is successful with diagnostic response within 2s");
    }
    else {
        TestStepFail("", "DoIPTest_403 is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_404()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_404");
    TestCaseDescription("[Description] Verify each doip entity to return to diagnostic position, and then return to diagnostic response.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    // receive diagnostic positive
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "Receive true diagmostic positive response");
    }
    else {
        TestStepFail("", "DoIPTest_404 is failed");
    }

    // receive diagnostic message
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_message_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_404 is successful with diagnostic message response");
    }
    else {
        TestStepFail("", "DoIPTest_404 is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
    
}


// 405 is related to 411
testcase DoIPTest_405()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_405");
    TestCaseDescription("[Description] Verify that each doip entity should respond to the diagnostic negative confirmation for the abnormal system.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0D00  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request 0D00 to 0001
    funrel = TcpSend(tcpsocket, DoIPTest_405_req, elCount(DoIPTest_405_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_02", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_405 is successful with receive diagnostic negative message");
    }
    else {
        TestStepFail("", "DoIPTest_405 is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_406()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_406");
    TestCaseDescription("[Description] Verify that the diagnostic data can be sent when no route is activated..\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");

    // direct send diagnostic request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send message failed with result %d", funrel);
    }


    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_06", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_406 is successful with receive true diagnostic respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


testcase DoIPTest_407()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_407");
    TestCaseDescription("[Description] When the destination address in the diagnostic request message is invalid, the doip entity should return a negative acknowledgement.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x1333");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_407_req, elCount(DoIPTest_407_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_03", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_407 is successful with receive diagnostic negative message");
    }
    else {
        TestStepFail("", "DoIPTest_407 is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_408()
{    
    
    TestCaseTitle("Diagnostic", "DoIPTest_408");
    TestCaseDescription("[Description] When the message in the diagnostic request message is too large, the doip entity should return a negative acknowledgement.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0133");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    TestStepPass("", "DoIPTest_408 is successful with receive diagnostic negative message");

    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


// 409 is related to 410
testcase DoIPTest_409()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_409");
    TestCaseDescription("[Description] After verifying that the doip entity receives a negative acknowledgment, it should not receive a diagnostic message response.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0144");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_409_req, elCount(DoIPTest_409_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    // receive diagnostic nagetive message
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_03", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "DoIPTest_409 is receive diagnostic negative message");
    }
    else {
        TestStepFail("", "DoIPTest_409 is failed");
    }
    
    // receive diagnostic  message
    result = TestWaitForTextEvent("DoIPTest_409", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepFail("", "DoIPTest_409 is failed");
    }
    else {

        TestStepPass("", "DoIPTest_409 is successful with not receive diagnostic response message");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}


// 409 is related to 410
testcase DoIPTest_410()
{
    
    TestCaseTitle("Diagnostic", "DoIPTest_410");
    TestCaseDescription("[Description] Verify that the doip entity receives a negative acknowledgment and determines if the socket is disconnected.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0144");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_409_req, elCount(DoIPTest_409_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    // receive diagnostic nagetive message
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_03", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "DoIPTest_410 is receive diagnostic negative message");
    }
    else {
        TestStepFail("", "DoIPTest_410 is failed");
    }
    
    // restart send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStepPass ("", "DoIPTest_410 is successul with receive diagnostic response message");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}



// 405 is related to 411
testcase DoIPTest_411()
{

    TestCaseTitle("Diagnostic", "DoIPTest_411");
    TestCaseDescription("[Description] Verify that when the doip entity diagnostic message responds to a negative code 02, the socket connection should be disconnected.\n ");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0001");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x8001", "byte");


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request / code 0x02 message
    funrel = TcpSend(tcpsocket, DoIPTest_405_req, elCount(DoIPTest_405_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    // receive diagnostic nagetive message
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_02", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_411 is receive diagnostic negative message code is 0x02.");
    }
    else {
        TestStepFail("", "DoIPTest_411 is failed");
    }
    
    // restart send diagnostic request/ Failure means success
    TestWaitForTimeout(5000);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStepFail ("", "DoIPTest_411 is failed with send diagnostic message");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepPass("", "DoIPTest_411 is successul socket is disconnect with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepPass("", "DoIPTest_411 is successul socket is disconnect with result %d", funrel);
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    
}



testcase DoIPTest_501()
{
    
    TestCaseTitle("Alive check", "DoIPTest_501");
    TestCaseDescription("[Description] The alive check request data structure for each DoIP entity must be compliant.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01  Target_Address = 0x0003");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x0007", "byte");

    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send routing activation request Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive true routing activation response message");
    }
    else {

        TestStepFail("", "Do not Receive routing activation  response");
    }

    TestWaitForTimeout(120 * 1000);

    // doip entity alive check
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
    if (funrel == 0) {

        TestStepPass ("", "Send doip entity alive check Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity alive check Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity alive check Message failed with result %d", funrel);
    }
    
    
    // 240s
    TestWaitForTimeout(240 * 1000);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send routing activation request Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_501 is successful with Live check is in effect");
    }
    else {

        TestStepFail("", "Do not Receive routing activation  response");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(2000);
    
}

testcase DoIPTest_502()
{
    
    TestCaseTitle("Alive check", "DoIPTest_502");
    TestCaseDescription("[Description] Verify that the doip entity should recognize the alive check information.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x0007", "byte");
  
    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send routing activation request Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive true routing activation response message");
    }
    else {

        TestStepFail("", "Do not Receive routing activation  response");
    }
    TestWaitForTimeout(1000);


    // doip entity alive check
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Response, elCount(DoIPTest_Vehicle_Alive_Check_Response));
    if (funrel == 0) {

        TestStepPass ("", "DoIPTest_502 si successful and not receive error message");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity alive check Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity alive check Message failed with result %d", funrel);
    }
    

    TCPoff(tcpsocket);
    TestWaitForTimeout(2000);
    
}



testcase DoIPTest_503()
{
    
    TestCaseTitle(" Alive check", "DoIPTest_503");
    TestCaseDescription("[Description] Verify that each doip entity should not recognize the alive check information.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400  3,Source_Address = 0x0E01");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PAYLOAD TYPE", "0x0007", "byte");
  
    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send routing activation request Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request Message failed with result %d",funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation response message");
    }
    else {

        TestStepFail("", "Do not Receive routing activation  response");
    }
    

    // doip entity alive check
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Alive_Check_Request, elCount(DoIPTest_Vehicle_Alive_Check_Request));
    if (funrel == 0) {

        TestStep ("", "Send doip entity alive check Message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity alive check Message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity alive check Message failed with result %d", funrel);
    }
    
    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIPTest_504", 10);
    if (funrel == 1) {
        
        TestStepFail("", "DoIPTest_503 is failed with do not receive alive check message response");
    }
    else {

        TestStepPass("", "DoIPTest_503 is successful with not receive true doip entity alive check message response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout (2000);
    
}


testcase DoIPTest_601()
{
    
    TestCaseTitle("Diagnostic power mode", "DoIPTest_601");
    TestCaseDescription("[Description] Each DoIP entity shall support the diagnostic power mode information request as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Power_Mode_Request, elcount(DoIPTest_Vehicle_Power_Mode_Request));
    if (funrel == 0) {

        TestStep("", "Send vehicle power mode message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle power mode message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {

        TestStepFail("", "Send vehicle power mode message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_power_mode_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_601 is successful with receive true vehicle power message mode response");
    }
    else {

        TestStepFail("", "DoIPTest_601 is failed with do not Receive vehicle power mode message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_602()
{
    
    TestCaseTitle("Diagnostic power mode", "DoIPTest_602");
    TestCaseDescription("[Description] Each DoIP entity shall support the diagnostic power mode information response as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Power_Mode_Request, elcount(DoIPTest_Vehicle_Power_Mode_Request));
    if (funrel == 0) {

        TestStep("", "Send vehicle power mode message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle power mode message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {

        TestStepFail("", "Send vehicle power mode message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_power_mode_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_602 is successful with receive true vehicle power message mode response");
    }
    else {

        TestStepFail("", "DoIPTest_602 is failed with do not Receive vehicle power mode message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_603()
{
    
    TestCaseTitle("Diagnostic power mode", "DoIPTest_603");
    TestCaseDescription("[Description] A DoIP entity shall respond with a diagnostic power mode information response within A_DoIP_ Ctrl after having received a previous diagnostic power mode information request.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Power_Mode_Request, elcount(DoIPTest_Vehicle_Power_Mode_Request));
    if (funrel == 0) {

        TestStep("", "Send vehicle power mode message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle power mode message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle power mode message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_power_mode_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_603 is successful with receive true vehicle power message mode response within 2s");
    }
    else {

        TestStepFail("", "DoIPTest_603 is failed with do not Receive vehicle power mode message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_701()
{
    
    TestCaseTitle("DoIP entity status", "DoIPTest_701");
    TestCaseDescription("[Description] Each DoIP entity shall implement the DoIP entity status request as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Entity_Status_Request, elcount(DoIPTest_Vehicle_Entity_Status_Request));
    if (funrel == 0) {

        TestStep ("", "Send doip entity status message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity status message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity status message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_entity_status_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_701　is successful　and doip stack server identified the request");
    }
    else {

        TestStepFail("", "Do not Receive Send doip entity status message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}

testcase DoIPTest_702()
{
    
    TestCaseTitle("DoIP entity status", "DoIPTest_702");
    TestCaseDescription("[Description] DoIP entity shall implement the DoIP entity status response as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Entity_Status_Request, elcount(DoIPTest_Vehicle_Entity_Status_Request));
    
    if (funrel == 0) {

        TestStep ("", "Send doip entity status message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity status message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity status message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_entity_status_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_702 successful　and Receive true Send doip entity status message response");
    }
    else {

        TestStepFail("", "Do not Receive Send doip entity status message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_703()
{
    
    TestCaseTitle("DoIP entity status", "DoIPTest_703");
    TestCaseDescription("[Description] The DoIP entity shall respond in A_DoIP_Ctrl [2s] udpon receipt of the previous DoIP entity status request.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Entity_Status_Request, elcount(DoIPTest_Vehicle_Entity_Status_Request));
    
    if (funrel == 0) {

        TestStep ("", "Send doip entity status message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity status message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity status message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_entity_status_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_703 successful　and Receive true Send doip entity status message response within 2s");
    }
    else {

        TestStepFail("", "Do not Receive Send doip entity status message response");
    }
    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);
    
}


testcase DoIPTest_801()
{
    
    TestCaseTitle("DoipTiming", "DoIPTest_801");
    TestCaseDescription("[Description] Each DoIP entity shall implement an individual general inactivity timer for each supported TCP_ DATA socket.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "Receive routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    
    TestWaitForTimeout(1000 * 305);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "DoIPTest_801 is fail");
    }
    else {

        TestStepPass("", "DoIPTest_801 is successful Five minutes later, TCP was down");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

}


testcase DoIPTest_802()
{
    
    TestCaseTitle("DoipTiming", "DoIPTest_802");
    TestCaseDescription("[Description] Each DoIP entity shall implement an individual general inactivity timer for each supported TCP_ DATA socket.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "Receive routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    
    TestWaitForTimeout(1000 * 305);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "DoIPTest_802 is fail");
    }
    else {

        TestStepPass("", "DoIPTest_802 is successful Five minutes later, TCP was down");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout (1000);

}


testcase DoIPTest_803()
{

    TestCaseTitle("DoipTiming", "DoIPTest_803");
    TestCaseDescription("[Description] The client receives the vehicle discovery response within A_DoIP_Ctrl[2s].\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("PAYLOAD_TYPE", "0001", "int");

    Udp_On(0);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));
    
    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message is successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString );
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_803 is successful receives the vehicle discovery response within A_DoIP_Ctrl[2s]");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_803 vehicle identity message response within A_DoIP_Ctrl[2s]");
    }

    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_901()
{
    
    TestCaseTitle("DoIP entity functional", "DoIPTest_901");
    TestCaseDescription("[Description] Verify functionality addressing for only one node.\n");
    TestCaseDescription("[Parameters] 1,Port = 13400  2,Function Address = 0xE400 = 0001");      
    TestCaseReportMeasuredValue("LOGIC_ADDRESS", "0xE400", "byte");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");

    // routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {
        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    TestWaitForTimeout (1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Function_Request, elCount(DoIPTest_Vehicle_Diagnostic_Function_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic function address Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic function address Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString );
    }
    else {

        TestStepFail("", "Send diagnostic function address Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_901 is successful Receive diagnostic function address Message respond");
    }
    else {

        TestStepFail ("", "Do not Receive diagnostic function address Message respond");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout (1000);

}


testcase DoIPTest_902()
{

    TestCaseTitle("DoIP entity functional", "DoIPTest_902");
    TestCaseDescription("[Description] Verify functionality addressing for only two node.\n");
    TestCaseDescription("[Parameters] 1,Port = 13400  2,Function Address = 0xE401 = 0001 0130");      
    TestCaseReportMeasuredValue("LOGIC_ADDRESS", "0xE300", "byte");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");

    // routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    TestWaitForTimeout (1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_902_req, elCount(DoIPTest_902_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic function address Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic function address Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic function address Message failed with result %d", funrel);
    }


    // first diagnostic positive message response
    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_902 is successful and Receive diagnostic function address Message respond");
    }
    else {

        TestStepFail ("", "Do not Receive diagnostic function address Message respond");
    }


    // second diagnostic positive message response
    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_positive_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_902 is successful and Receive diagnostic function address Message respond");
    }
    else {

        TestStepFail ("", "Do not Receive diagnostic function address Message respond");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout (1000);  

}


testcase DoIPTest_903()
{

    TestCaseTitle("DoIP entity functional", "DoIPTest_903");
    TestCaseDescription("[Description] Verify Functional addressing non-existent diagnostic group.\n");
    TestCaseDescription("[Parameters] 1,Port = 13400  2,Function Address = 0xE500.");      
    TestCaseReportMeasuredValue("LOGIC_ADDRESS", "0xE500", "byte");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");

    // routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    TestWaitForTimeout (1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_903_req, elCount(DoIPTest_903_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic function address Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic function address Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic function address Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_03", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_903 is Successful and Receive diagnostic function address Message NACK respond");
    }
    else {

        TestStepFail("", "Do not Receive diagnostic function address Message respond");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout (1000);  

}


testcase DoIPTest_904()
{

    TestCaseTitle("DoIP entity functional", "DoIPTest_904");
    TestCaseDescription("[Description] Verify that the function address has the wrong original address.\n");
    TestCaseDescription("[Parameters] 1,Port = 13400  2,Source Address = 0x0500.");      
    TestCaseReportMeasuredValue("LOGIC_ADDRESS", "0x0500", "byte");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");

    // routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send route activation request Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStep("", "Receive routing activation respond message");
    }
    else {

        TestStepFail ("", "Do not Receive routing activation respond message");
    }
    TestWaitForTimeout (1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_904_req, elCount(DoIPTest_904_req));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic function address Message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic function address Message is failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic function address Message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_negative_code_02", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepPass("", "DoIPTest_904 is Successful and Receive diagnostic function address Message NACK respond");
    }
    else {

        TestStepFail("", "Do not Receive diagnostic function address Message respond");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout (1000);  

}



testcase DoIPTest_1001()
{

    TestCaseTitle("Vehicle Announce", "DoIPTest_1001");
    TestCaseDescription("[Description] External test equipment should listen on port UDP DISCOVERY.\n ");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,IP = 255.255.255.255  4,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    // send doip stack debug testcase message
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, vehicle_announce, elcount(vehicle_announce));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1001 is successful with receive true vehicle announcement message response");
    }
    else {

        TestStepFail("", "DoIPTest_1001 is failed wih not Receive vehicle announcement message response");
    }

    Udp_Off();
    TestWaitForTimeout(1000);

}


// need to restart the doip server
testcase DoIPTest_1002()
{

    TestCaseTitle("Vehicle Announce", "DoIPTest_1002");
    TestCaseDescription("[Description] The SUT should ignore vehicle announcements where the source port is not UDP_DISCOVERY.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,IP = 255.255.255.255  4,UDP PORT = 13401");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13401", "int");


    // send doip stack debug testcase message
    Udp_On(TEST_PORT_ONE);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, vehicle_announce_other_ports, elcount(vehicle_announce_other_ports));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }
    
    udprec();
    funrel = TestWaitForTextEvent("DoIPTest_1002", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepFail("", "DoIPTest_1002 is failed with receive vehicle announcement message response");
    }
    else {

        TestStepPass("", "DoIPTest_1002 is successful with not receive vehicle announcement message response");
    }

    Udp_Off();
    TestWaitForTimeout(1000);
    

}


testcase DoIPTest_1003()
{

    TestCaseTitle("Vehicle Announce", "DoIPTest_1003");
    TestCaseDescription("[Description] Verify that the source port of the Udp connection is udp_test_hangment_request and that the response port corresponds to that. \n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "49152~65535", "int");

    Udp_On(0);
    funrel = UdpSendTo(udpsocket, Broadcast_address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Identity_Request, elcount(DoIPTest_Vehicle_Identity_Request));

    if (funrel == 0) {

        TestStep ("", "Send vehicle identity request message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send vehicle identity request message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send vehicle identity request message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Ctrl + 50); // 50ms network delay

    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1003 is successful with receive true vehicle identity request message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1003 vehicle identity request message response");
    }

    Udp_Off();
    TestWaitForTimeout (1000);

}

testcase DoIPTest_1004()
{

        
    TestCaseTitle("Vehicle Announce", "DoIPTest_1004");
    TestCaseDescription("[Description] Verify that each DoIP entity should send A_DoIP_Announce_Num [3] secondary vehicle announcements at intervals of A_DoIP_Announce_Interval after configuring a valid IP address.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    count = 0;
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, vehicle_announce, elcount(vehicle_announce));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval * 30);
    if (funrel == 1) {

        count++;
        TestStep("", "First vehicle announcement response received");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1004 response");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval + 20);
    if (funrel == 1) {

        count++;
        TestStep("", "Receive the second vehicle announcement response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1004 response");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval + 20);
    if (funrel == 1) {

        count++;
        TestStep("", "Response to the third vehicle announcement received");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1004 response");
    }
    
    if (count == 3) {
        
        TestStepPass("", "DoIPTest_1004 is successful");
    }
    else {
        
        TestStepFail("", "DoIPTest_1004 is failed");
    }

    count = 0;
    TestWaitForTimeout(1000);
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_1005()
{
        
    TestCaseTitle("Vehicle Announce", "DoIPTest_1005");
    TestCaseDescription("[Description] Verify the time interval of doip stack entity vehicle announcement every 500ms after configuring a valid IP address.\n");
    TestCaseDescription("[Parameters] 1,IP = 255.255.255.255  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");
    
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, vehicle_announce, elcount(vehicle_announce));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval * 30);
    if (funrel == 1) {

        TestStep("", "First vehicle announcement response received in A_DoIP_Announce_Interval");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1005 response");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval + 20);
    if (funrel == 1) {

        TestStep("", "Receive the second vehicle announcement response in A_DoIP_Announce_Interval");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1005 response");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_identity_response", A_DoIP_Announce_Interval + 20);
    if (funrel == 1) {

        TestStep("", "Response to the third vehicle announcement received in A_DoIP_Announce_Interval");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1005 response");
    }
    
    TestStepPass("", "DoIPTest_1005 is successful");

    TestWaitForTimeout(1000);
    Udp_Off();
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_1101()
{
    
    TestCaseTitle("DoIP debug case", "DoIPTest_1101");
    TestCaseDescription("[Description] Each DoIP entity shall implement the DoIP entity status request as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400.");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // Send message change status 
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_node, elcount(entity_type_node));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase message is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase message is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_entity_status", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }


    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, DoIPTest_Vehicle_Entity_Status_Request, elcount(DoIPTest_Vehicle_Entity_Status_Request));
    if (funrel == 0) {

        TestStep ("", "Send doip entity status message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(udpsocket) != 997)) {

        IpGetLastSocketErrorAsString(udpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send doip entity status message failed with result %d (%s)", IpGetLastSocketError(udpsocket), errorString);
    }
    else {

        TestStepFail("", "Send doip entity status message failed with result %d", funrel);
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_vehicle_entity_status_response", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1101 successful　and doip stack server entity response !");
    }
    else {

        TestStepFail("", "Do not Receive Send doip entity status message response");
    }
    
    
    // change doip entity status
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, entity_type_gateway, elcount(entity_type_gateway));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_1102()
{
    
    TestCaseTitle("DoIP debug case", "DoIPTest_1102");
    TestCaseDescription("[Description] Each DoIP entity shall support the diagnostic power mode information request as specified.\n");
    TestCaseDescription("[Parameters] 1,IP = 192.168.50.1  2,Port = 13400");
    TestCaseReportMeasuredValue("IP", "192.168.50.1", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, power_mode_false, elcount(power_mode_false));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_power_mode", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }


    // send routing activation request
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message is Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket)!=997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else
    {
        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStep("", "Receive true routing activation respond message");
    }
    else {

        TestStepFail("", "Do not receive routing activation respond message");
    }
    TestWaitForTimeout(1000);


    // send diagnostic request
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Diagnostic_Request, elCount(DoIPTest_Vehicle_Diagnostic_Request));
    if (funrel == 0) {

        TestStep ("", "Send diagnostic message Successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997)) {

        IpGetLastSocketErrorAsString( tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send diagnostic message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send diagnostic message failed with result %d", funrel);
    }

    result = TestWaitForTextEvent("DoIP_vehicle_diagnostic_message_response", A_DoIP_Diagnostic_Message + 50);
    if (result == 1) {

        TestStepFail("", "DoIPTest_1102 is failed with The diagnostic response data has the different address");
    }
    else {
        TestStepPass("", "DoIPTest_1102 is successful with diagnostic request is failed");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);



    // send debug change status message
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, power_mode_true, elcount(power_mode_true));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    
    TestWaitForTimeout (2000);
    Udp_Off();
    TestWaitForTimeout (1000);

}


testcase DoIPTest_1103()
{

    TestCaseTitle("DoIP debug case", "DoIPTest_1103");
    TestCaseDescription("[Description] When the enable line is in the false state, no related operation can be performed.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "49152~65535", "int");

    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, activation_line_false, elcount(activation_line_false));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_header_resolution_failure_code_04", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }



    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepFail("", "Do Receive DoIPTest_1103 response");
    }
    else {

        TestStepPass("", "DoIPTest_1103 is successful");
    }
    

    
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, activation_line_true, elcount(activation_line_true));
    if (funrel == 0) {

        TestStep("", "Doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);
    Udp_Off();
    TestWaitForTimeout(1000);

}


testcase DoIPTest_1104()
{

    TestCaseTitle("DoIP debug case", "DoIPTest_1104");
    TestCaseDescription("[Description] Verify authentication logic for route activation\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, routing_activation_auth_true, elcount(routing_activation_auth_true));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_routing_activation_auth", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }

    // send routing activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_1104_req, elCount(DoIPTest_1104_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1104 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1104 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    Udp_Off();
    TestWaitForTimeout(1000);
    
}


testcase DoIPTest_1105()
{

    TestCaseTitle("DoIP debug case", "DoIPTest_1105");
    TestCaseDescription("[Description] Verify logic when route activation does not require authentication.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");


    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, routing_activation_auth_false, elcount(routing_activation_auth_false));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_routing_activation_not_auth", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Receive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }


    // send routing activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_Vehicle_Routing_Activation_Request, elCount(DoIPTest_Vehicle_Routing_Activation_Request));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_response", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1105 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1105 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    Udp_Off();
    TestWaitForTimeout(1000);
    
}



testcase DoIPTest_1106()
{

    TestCaseTitle("DoIP debug case", "DoIPTest_1106");
    TestCaseDescription("[Description] Verify failure when route activation requires authentication.\n");
    TestCaseDescription("[Parameters] 1,Protocol version = 0x02  2,Inverse protocol version = 0xFD  3,Port = 13400");
    TestCaseReportMeasuredValue("IP", "255.255.255.255", "string");
    TestCaseReportMeasuredValue("PORT", "13400", "int");

    // send debug testcase change status
    Udp_On(UDP_DISCOVERY_PROT);
    funrel = UdpSendTo(udpsocket, DoIP_Server_Address, UDP_DISCOVERY_PROT, routing_activation_auth_true, elcount(routing_activation_auth_true));
    if (funrel == 0) {

        TestStep("", "Send doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Send doip stack debug testcase change status is failed");
    }

    udprec();
    funrel = TestWaitForTextEvent("DoIP_debug_doip_routing_activation_auth", A_DoIP_Ctrl + 50);
    if (funrel == 1) {

        TestStepPass("", "Reveive doip stack debug testcase change status is successful");
    }
    else {

        TestStepFail("", "Doip stack debug testcase change status is failed");
    }


    // send routing activation request message
    tcpsocket = TCPon(TCP_DATA_PROT);
    funrel = TcpSend(tcpsocket, DoIPTest_1106_req, elCount(DoIPTest_1106_req));
    if (funrel == 0) {

        TestStep ("", "Send routing activation request message successful");
    }
    else if ((funrel == -1) && (IpGetLastSocketError(tcpsocket) != 997 )) {

        IpGetLastSocketErrorAsString(tcpsocket, errorString, elcount(errorString));
        TestStepFail("", "Send routing activation request message failed with result %d (%s)", IpGetLastSocketError(tcpsocket), errorString);
    }
    else {

        TestStepFail("", "Send routing activation request message failed with result %d", funrel);
    }

    tcprec(tcpsocket);   
    funrel = TestWaitForTextEvent("DoIP_vehicle_routing_activation_NACK_code_04", A_DoIP_Diagnostic_Message + 50);
    if (funrel == 1) {

        TestStepPass("", "DoIPTest_1105 is successful with receive routing activation message response");
    }
    else {

        TestStepFail("", "Do not Receive DoIPTest_1105 response");
    }
    
    TCPoff(tcpsocket);
    TestWaitForTimeout(1000);

    Udp_Off();
    TestWaitForTimeout(1000);
    
}



// Get the IP address of DUT
void get_dut_broadcast_address()
{
    funrel = sysGetVariableString(sysvar::ECU::D_Broadcast_address, Tmp_address, elcount(Tmp_address));
    if (funrel == 0) {
        TestStep("", "Get DUT D_Broadcast_address Successful : %s", Tmp_address);
    }
    else {
        TestStepFail("", "Get DUT D_Broadcast_address failed with result %d : %s", funrel, Tmp_address);
    }
    Broadcast_address = IpGetAddressAsNumber(Tmp_address);
    //TestStep("","Converting IPv4 Address %s to numerical value => 0x%x", Tmp_address, Broadcast_address);
}



//Get the IP address of DUT
void get_dut_server_address()
{
    funrel = sysGetVariableString(sysvar::ECU::D_DoIP_Server, Tmp_address, elcount(Tmp_address));
    
    if (funrel == 0) {

        TestStep("", "Get D_DoIP_Server Successful : %s", Tmp_address);
    }
    else {

        TestStepFail("", "Get D_DoIP_Server failed with result %d : %s", funrel, Tmp_address);
    }
    DoIP_Server_Address = IpGetAddressAsNumber(Tmp_address);
}


//Get the logic address of DUT
void get_dut_server_logic_address()
{
    sysGetVariableData(sysvar::ECU::D_LogAdd, DoIP_Logic_address, Logic_address_length);
    TestStep("", "DoIP logic address is 0x%x %x", DoIP_Logic_address[0], DoIP_Logic_address[1]);
}


//Get the IP address and logical address of the tester
void get_tester_address()
{
    funrel = sysGetVariableString(sysvar::Tester::T_Address, Tmp_address, elcount(Tmp_address));
    if (funrel == 0) {

        TestStep("", "Get T_Address address Successful : %s", Tmp_address);
    }
    else {

        TestStep("", "Get TesT_Addresster address failed with result %d : %s", funrel, Tmp_address);
    }
    Tester_address = IpGetAddressAsNumber(Tmp_address);
}


//Get the logic address of Tester
void get_dut_tester_logic_address()
{
    sysGetVariableData(sysvar::Tester::T_LogAdd, Tester_Logic_address, Logic_address_length);
    TestStep("", "Tester logic address is 0x%x %x", Tester_Logic_address[0], Tester_Logic_address[1]);
}


//Get the vehicle vin
void get_vehicle_vin()
{    
    funrel = sysGetVariableString(sysvar::ECU::D_VIN, Vehicle_VIN, elcount(Vehicle_VIN));
    if (0 == funrel) {

        TestStep("", "Get Vehicle VIN Successful : %s", Vehicle_VIN);
    }
    else {

        TestStep("", "Get Vehicle VIN failed : %s", Vehicle_VIN);
    }
}


//Get the vehicle vin
void get_vehicle_eid()
{    
    funrel = sysGetVariableString(sysvar::ECU::D_EID, Vehicle_EID, elcount(Vehicle_EID));
    if (0 == funrel) {

        TestStep("", "Get Vehicle EID Successful : %s", Vehicle_EID);
    }
    else {
        
        TestStep("", "Get Vehicle EID failed : %s", Vehicle_EID);
    }
}


//Get the vehicle vin
void get_vehicle_gid()
{    
    funrel = sysGetVariableString(sysvar::ECU::D_GID, Vehicle_GID, elcount(Vehicle_GID));
    if (0 == funrel) {

        TestStep("", "Get Vehicle GID Successful : %s", Vehicle_GID);
    }
    else {
        
        TestStep("", "Get Vehicle GID failed : %s", Vehicle_GID);
    }
}
