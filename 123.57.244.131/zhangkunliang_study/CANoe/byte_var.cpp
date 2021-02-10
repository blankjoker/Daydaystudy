

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
