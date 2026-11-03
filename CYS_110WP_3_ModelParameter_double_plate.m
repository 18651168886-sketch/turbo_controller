% 参数
% 以PF开头的需要在主程序中定义成全局变量，生成代码中只读
clearvars;
clc
% 档位信息存储模块uint
PF_Gear_Info = single([40000; 45000; 50000; 55000; 57000; 59000; 60000; 61000; 61000; 61000; 61000; 61000]);
PF_ACCFULLRANGE = single(3360);
PF_K_TiaoJie = 1;

%%%%%%%%通讯信息、配置信息和复位信息%%%%%%%%%%%%
PF_MyUsart2_Rxdata = uint8(zeros(50,1));
% PF_MyUsart2_Rxdata(7)=5000;
PF_MySet_Rxdata = uint8(zeros(50,1));%配置信息数组，从第15至19位分别以两个字节表示起动过程燃油压力限值、第一阶段油门、第二阶段油门、最后G阶段等待时间以及控制参数整体缩放参数
PF_Reset_Information = uint8(zeros(20,1));
PF_MyUsart1_Rxdata = uint8(zeros(50,1));

%%%%%%%%新增部分，传感器标定%%%%%%%%%%%%
PF_Sensor_X1_T4 = single([0 4095]);
PF_Sensor_Y1_T4 = single([0 3.0]);
PF_Sensor_X2_T4 = single([0 1.666667]);
PF_Sensor_Y2_T4 = single([0 5000]);
PF_Sensor_X3_T4 = single([0 504 999 1497 2010 2529 3051 3568 4076 4571 4959]);
PF_Sensor_Y3_T4 = single([0 100 200 300 400 500 600 700 800 900 980]);

PF_Sensor_X_P2 = single([0.5 3.0]);
PF_Sensor_Y_P2 = single([0.0 1000.0]);

PF_Sensor_X_Poil = single([0.5 3.0]);
PF_Sensor_Y_Poil = single([0.0 1000.0]);

PF_Sensor_X_T1t = single([-50 300]);
PF_Sensor_Y_T1t = single([-50 300]);

PF_Sensor_X_Vpump = single([0 3.0]);
PF_Sensor_Y_Vpump = single([0 33]);

PF_Sensor_X_Vpower = single([0 3.0]);
PF_Sensor_Y_Vpower = single([0 33]);

%%%%第一个输出，为常规控制量输出%%%%%%%%
EngineControl_Out = Simulink.Bus;
EngineControl_Out.DataScope = 'Exported';
EngineControl_Out_elems1 = Simulink.BusElement;
EngineControl_Out_elems2 = Simulink.BusElement;
EngineControl_Out_elems3 = Simulink.BusElement;
EngineControl_Out_elems4 = Simulink.BusElement;
EngineControl_Out_elems5 = Simulink.BusElement;
EngineControl_Out_elems6 = Simulink.BusElement;
EngineControl_Out_elems7 = Simulink.BusElement;
EngineControl_Out_elems8 = Simulink.BusElement;
EngineControl_Out_elems9 = Simulink.BusElement;
EngineControl_Out_elems10 = Simulink.BusElement;
EngineControl_Out_elems11 = Simulink.BusElement;
EngineControl_Out_elems12 = Simulink.BusElement;
EngineControl_Out_elems13 = Simulink.BusElement;
EngineControl_Out_elems14 = Simulink.BusElement;
EngineControl_Out_elems15 = Simulink.BusElement;
EngineControl_Out_elems16 = Simulink.BusElement;
EngineControl_Out_elems17 = Simulink.BusElement;
EngineControl_Out_elems18 = Simulink.BusElement;

EngineControl_Out_elems1.Name = 'EValve_Cycle';
EngineControl_Out_elems1.DataType = 'uint16';
EngineControl_Out_elems2.Name = 'EValve_Open';
EngineControl_Out_elems2.DataType = 'uint16';
EngineControl_Out_elems3.Name = 'Eblast_Cycle';
EngineControl_Out_elems3.DataType = 'uint16';
EngineControl_Out_elems4.Name = 'Eblast_Open';
EngineControl_Out_elems4.DataType = 'uint16';
EngineControl_Out_elems5.Name = 'Motor_Cycle';
EngineControl_Out_elems5.DataType = 'uint16';
EngineControl_Out_elems6.Name = 'Motor_Open';
EngineControl_Out_elems6.DataType = 'uint16';
EngineControl_Out_elems7.Name = 'EValve_Enable';
EngineControl_Out_elems7.DataType = 'uint8';
EngineControl_Out_elems8.Name = 'Eblast_Enable';
EngineControl_Out_elems8.DataType = 'uint8';
EngineControl_Out_elems9.Name = 'Motor_Enable';
EngineControl_Out_elems9.DataType = 'uint8';
EngineControl_Out_elems10.Name = 'SWO_Firework';
EngineControl_Out_elems10.DataType = 'uint8';
EngineControl_Out_elems11.Name = 'SWO_BleedAir';
EngineControl_Out_elems11.DataType = 'uint8';
EngineControl_Out_elems12.Name = 'EngineState';
EngineControl_Out_elems12.DataType = 'uint8';
EngineControl_Out_elems13.Name = 'Flag_ECUReset_Clear';
EngineControl_Out_elems13.DataType = 'uint8';
EngineControl_Out_elems14.Name = 'Flag_ECUReset_Save';
EngineControl_Out_elems14.DataType = 'uint8';
EngineControl_Out_elems15.Name = 'Flag_Reset_Enable';
EngineControl_Out_elems15.DataType = 'uint8';
EngineControl_Out_elems16.Name = 'Accelerator';
EngineControl_Out_elems16.DataType = 'single';
EngineControl_Out_elems17.Name = 'Nc_dem';
EngineControl_Out_elems17.DataType = 'single';
EngineControl_Out_elems18.Name = 'Nc';
EngineControl_Out_elems18.DataType = 'single';
 
EngineControl_Out.Elements = [EngineControl_Out_elems1,EngineControl_Out_elems2,EngineControl_Out_elems3,EngineControl_Out_elems4,EngineControl_Out_elems5,EngineControl_Out_elems6,EngineControl_Out_elems7,EngineControl_Out_elems8,EngineControl_Out_elems9,EngineControl_Out_elems10,EngineControl_Out_elems11,EngineControl_Out_elems12,EngineControl_Out_elems13,EngineControl_Out_elems14,EngineControl_Out_elems15,EngineControl_Out_elems16,EngineControl_Out_elems17,EngineControl_Out_elems18];
%%%%第二个输出，为保存输出%%%%%%%%
SaveData_Out = Simulink.Bus;
SaveData_Out.DataScope = 'Exported';
SaveData_Out_elems1 = Simulink.BusElement;
SaveData_Out_elems2 = Simulink.BusElement;
SaveData_Out_elems3 = Simulink.BusElement;
SaveData_Out_elems4 = Simulink.BusElement;
SaveData_Out_elems5 = Simulink.BusElement;
SaveData_Out_elems6 = Simulink.BusElement;
SaveData_Out_elems7 = Simulink.BusElement;
SaveData_Out_elems8 = Simulink.BusElement;
SaveData_Out_elems9 = Simulink.BusElement;
SaveData_Out_elems10 = Simulink.BusElement;
SaveData_Out_elems11 = Simulink.BusElement;
SaveData_Out_elems12 = Simulink.BusElement;
SaveData_Out_elems13 = Simulink.BusElement;
SaveData_Out_elems14 = Simulink.BusElement;
SaveData_Out_elems15 = Simulink.BusElement;
SaveData_Out_elems16 = Simulink.BusElement;
SaveData_Out_elems17 = Simulink.BusElement;
SaveData_Out_elems18 = Simulink.BusElement;
SaveData_Out_elems19 = Simulink.BusElement;
SaveData_Out_elems20 = Simulink.BusElement;
SaveData_Out_elems21 = Simulink.BusElement;
SaveData_Out_elems22 = Simulink.BusElement;
SaveData_Out_elems23 = Simulink.BusElement;
SaveData_Out_elems24 = Simulink.BusElement;
SaveData_Out_elems25 = Simulink.BusElement;


SaveData_Out_elems1.Name = 'savedata1';
SaveData_Out_elems1.DataType = 'single';
SaveData_Out_elems2.Name = 'savedata2';
SaveData_Out_elems2.DataType = 'single';
SaveData_Out_elems3.Name = 'savedata3';
SaveData_Out_elems3.DataType = 'single';
SaveData_Out_elems4.Name = 'savedata4';
SaveData_Out_elems4.DataType = 'single';
SaveData_Out_elems5.Name = 'savedata5';
SaveData_Out_elems5.DataType = 'single';
SaveData_Out_elems6.Name = 'savedata6';
SaveData_Out_elems6.DataType = 'single';
SaveData_Out_elems7.Name = 'savedata7';
SaveData_Out_elems7.DataType = 'single';
SaveData_Out_elems8.Name = 'savedata8';
SaveData_Out_elems8.DataType = 'single';
SaveData_Out_elems9.Name = 'savedata9';
SaveData_Out_elems9.DataType = 'single';
SaveData_Out_elems10.Name = 'savedata10';
SaveData_Out_elems10.DataType = 'single';
SaveData_Out_elems11.Name = 'savedata11';
SaveData_Out_elems11.DataType = 'single';
SaveData_Out_elems12.Name = 'savedata12';
SaveData_Out_elems12.DataType = 'single';
SaveData_Out_elems13.Name = 'savedata13';
SaveData_Out_elems13.DataType = 'single';
SaveData_Out_elems14.Name = 'savedata14';
SaveData_Out_elems14.DataType = 'single';
SaveData_Out_elems15.Name = 'savedata15';
SaveData_Out_elems15.DataType = 'single';
SaveData_Out_elems16.Name = 'savedata16';
SaveData_Out_elems16.DataType = 'single';
SaveData_Out_elems17.Name = 'savedata17';
SaveData_Out_elems17.DataType = 'single';
SaveData_Out_elems18.Name = 'savedata18';
SaveData_Out_elems18.DataType = 'single';
SaveData_Out_elems19.Name = 'savedata19';
SaveData_Out_elems19.DataType = 'single';
SaveData_Out_elems20.Name = 'savedata20';
SaveData_Out_elems20.DataType = 'single';
SaveData_Out_elems21.Name = 'savedata21';
SaveData_Out_elems21.DataType = 'single';
SaveData_Out_elems22.Name = 'savedata22';
SaveData_Out_elems22.DataType = 'single';
SaveData_Out_elems23.Name = 'savedata23';
SaveData_Out_elems23.DataType = 'single';
SaveData_Out_elems24.Name = 'savedata24';
SaveData_Out_elems24.DataType = 'single';
SaveData_Out_elems25.Name = 'savedata25';
SaveData_Out_elems25.DataType = 'single';
SaveData_Out.Elements = [SaveData_Out_elems1,SaveData_Out_elems2,SaveData_Out_elems3,SaveData_Out_elems4,SaveData_Out_elems5,SaveData_Out_elems6,SaveData_Out_elems7,SaveData_Out_elems8,SaveData_Out_elems9,SaveData_Out_elems10,SaveData_Out_elems11,SaveData_Out_elems12,SaveData_Out_elems13,SaveData_Out_elems14,SaveData_Out_elems15,SaveData_Out_elems16,SaveData_Out_elems17,SaveData_Out_elems18,SaveData_Out_elems19,SaveData_Out_elems20,SaveData_Out_elems21,SaveData_Out_elems22,SaveData_Out_elems23,SaveData_Out_elems24,SaveData_Out_elems25];

%%%%第三个输出，为通讯输出%%%%%%%%
SendData_Out = Simulink.Bus;
SendData_Out.DataScope = 'Exported';
SendData_Out_elems1 = Simulink.BusElement;
SendData_Out_elems2 = Simulink.BusElement;
SendData_Out_elems3 = Simulink.BusElement;
SendData_Out_elems4 = Simulink.BusElement;
SendData_Out_elems5 = Simulink.BusElement;
SendData_Out_elems6 = Simulink.BusElement;
SendData_Out_elems7 = Simulink.BusElement;
SendData_Out_elems8 = Simulink.BusElement;
SendData_Out_elems9 = Simulink.BusElement;
SendData_Out_elems10 = Simulink.BusElement;
SendData_Out_elems11 = Simulink.BusElement;
SendData_Out_elems12 = Simulink.BusElement;
SendData_Out_elems13 = Simulink.BusElement;
SendData_Out_elems14 = Simulink.BusElement;
SendData_Out_elems15 = Simulink.BusElement;
SendData_Out_elems16 = Simulink.BusElement;
SendData_Out_elems17 = Simulink.BusElement;
SendData_Out_elems18 = Simulink.BusElement;
SendData_Out_elems19 = Simulink.BusElement;
SendData_Out_elems20 = Simulink.BusElement;
SendData_Out_elems21 = Simulink.BusElement;
SendData_Out_elems22 = Simulink.BusElement;
SendData_Out_elems23 = Simulink.BusElement;
SendData_Out_elems24 = Simulink.BusElement;
SendData_Out_elems25 = Simulink.BusElement;
SendData_Out_elems26 = Simulink.BusElement;
SendData_Out_elems27 = Simulink.BusElement;
SendData_Out_elems28 = Simulink.BusElement;
SendData_Out_elems29 = Simulink.BusElement;
SendData_Out_elems1.Name = 'senddata1';
SendData_Out_elems1.DataType = 'uint8';
SendData_Out_elems2.Name = 'senddata2';
SendData_Out_elems2.DataType = 'uint8';
SendData_Out_elems3.Name = 'senddata3';
SendData_Out_elems3.DataType = 'uint8';
SendData_Out_elems4.Name = 'senddata4';
SendData_Out_elems4.DataType = 'uint8';
SendData_Out_elems5.Name = 'senddata5';
SendData_Out_elems5.DataType = 'uint8';
SendData_Out_elems6.Name = 'senddata6';
SendData_Out_elems6.DataType = 'uint8';
SendData_Out_elems7.Name = 'senddata7';
SendData_Out_elems7.DataType = 'uint8';
SendData_Out_elems8.Name = 'senddata8';
SendData_Out_elems8.DataType = 'uint8';
SendData_Out_elems9.Name = 'senddata9';
SendData_Out_elems9.DataType = 'uint8';
SendData_Out_elems10.Name = 'senddata10';
SendData_Out_elems10.DataType = 'uint8';
SendData_Out_elems11.Name = 'senddata11';
SendData_Out_elems11.DataType = 'uint8';
SendData_Out_elems12.Name = 'senddata12';
SendData_Out_elems12.DataType = 'uint8';
SendData_Out_elems13.Name = 'senddata13';
SendData_Out_elems13.DataType = 'uint8';
SendData_Out_elems14.Name = 'senddata14';
SendData_Out_elems14.DataType = 'uint8';
SendData_Out_elems15.Name = 'senddata15';
SendData_Out_elems15.DataType = 'uint8';
SendData_Out_elems16.Name = 'senddata16';
SendData_Out_elems16.DataType = 'uint8';
SendData_Out_elems17.Name = 'senddata17';
SendData_Out_elems17.DataType = 'uint8';
SendData_Out_elems18.Name = 'senddata18';
SendData_Out_elems18.DataType = 'uint8';
SendData_Out_elems19.Name = 'senddata19';
SendData_Out_elems19.DataType = 'uint8';
SendData_Out_elems20.Name = 'senddata20';
SendData_Out_elems20.DataType = 'uint8';
SendData_Out_elems21.Name = 'senddata21';
SendData_Out_elems21.DataType = 'uint8';
SendData_Out_elems22.Name = 'senddata22';
SendData_Out_elems22.DataType = 'uint8';
SendData_Out_elems23.Name = 'senddata23';
SendData_Out_elems23.DataType = 'uint8';
SendData_Out_elems24.Name = 'senddata24';
SendData_Out_elems24.DataType = 'uint8';
SendData_Out_elems25.Name = 'senddata25';
SendData_Out_elems25.DataType = 'uint8';
SendData_Out_elems26.Name = 'senddata26';
SendData_Out_elems26.DataType = 'uint8';
SendData_Out_elems27.Name = 'senddata27';
SendData_Out_elems27.DataType = 'uint8';
SendData_Out_elems28.Name = 'senddata28';
SendData_Out_elems28.DataType = 'uint8';
SendData_Out_elems29.Name = 'senddata29';
SendData_Out_elems29.DataType = 'uint8';
SendData_Out.Elements = [SendData_Out_elems1,SendData_Out_elems2,SendData_Out_elems3,SendData_Out_elems4,SendData_Out_elems5,SendData_Out_elems6,SendData_Out_elems7,SendData_Out_elems8,SendData_Out_elems9,SendData_Out_elems10,SendData_Out_elems11,SendData_Out_elems12,SendData_Out_elems13,SendData_Out_elems14,SendData_Out_elems15,SendData_Out_elems16,SendData_Out_elems17,SendData_Out_elems18,SendData_Out_elems19,SendData_Out_elems20,SendData_Out_elems21,SendData_Out_elems22,SendData_Out_elems23,SendData_Out_elems24,SendData_Out_elems25,SendData_Out_elems26,SendData_Out_elems27,SendData_Out_elems28,SendData_Out_elems29];

% 以下为模型计算所需的辅助量，在代码生成中无需
% 复位标志
PF_Flag_rx_suc = uint8(1);
PF_Flag_ECUReset = uint8(0);
% 发动机特性
% 发动机转速归一化到百分比的值 N/86000*100
PE_RotaSpeed_Translate = 860;
% 发动机转速归一化到百分比的值 V/2880*100
PE_Pump_Translate = PF_ACCFULLRANGE/100;
PF_Kpu = 10;

PE_Kaer = [1.5402 1.5402 1.2264 1.0076 0.9481 0.7601 0.7111 0.569 0.5198 0.4926 0.5308 0.4325 0.4325]/PF_Kpu;
PE_Taer = [0.4870 0.4870 0.4021 0.3359 0.3118 0.2998 0.3382 0.2641 0.3687 0.2358 0.4394 0.3061 0.3061]*1.0142;
PE_Nr = [21 60.566 66.799 71.721 75.770 79.569 82.671 85.436 87.693 87.930 89.917 92.099 103]*1.0142;

%elems(1) = Simulink.BusElement;
%elems(1).Name = 'VALVE1';
%elems(1).Dimensions = 1;
%elems(1).DimensionsMode = 'Fixed';
%elems(1).DataType = 'double';
%elems(1).SampleTime = -1;
%elems(1).Complexity = 'real';

%发动机中临时使用参数，与生成代码无关
PL_EngineModel_Rotaspeed=[0 20000 96400];
PL_EngineModel_Temp_Exhaust=[500 500 500 500 500 500 500 500 500 500];
PL_EngineModel_Press_P2=[400 400 400 400 400 400 400 400 400 400];
PL_EngineModel_Actuator=[0 10 100];
PL_Nr=[50 60 70 80 90 100];
PL_Kaer=[0.1 0.1 0.1 0.1 0.1 0.1];
PL_Taer=[0.1 0.1 0.1 0.1 0.1 0.1];

PL_EngineModel_EngineStar_Time = [0.1 0.2 0.3	0.4	0.5	0.6	0.7	0.8	0.9	1	1.1	1.2	1.3	1.4	1.5	1.6	1.7	1.8	1.9	2	2.1	2.2	2.3	2.4	2.5	2.6	2.7	2.8	2.9	3	3.1	3.2	3.3	3.4	3.5	3.6	3.7	3.8	3.9	4	4.1	4.2	4.3	4.4	4.5	4.6	4.7	4.8	4.9	5	5.1	5.2	5.3	5.4	5.5	5.6	5.7	5.8	5.9	6	6.1	6.2	6.3	6.4	6.5	6.6	6.7	6.8	6.9	7	7.1	7.2	7.3	7.4	7.5	7.6	7.7	7.8	7.9	8	8.1	8.2	8.3	8.4	8.5	8.6	8.7	8.8	8.9	9	9.1	9.2	9.3	9.4	9.5	9.6	9.7	9.8	9.9	10	10.1	10.2	10.3	10.4	10.5	10.6	10.7	10.8	10.9	11	11.1	11.2	11.3	11.4	11.5	11.6	11.7	11.8	11.9	12	12.1	12.2	12.3	12.4	12.5	12.6	12.7]/2;
PL_EngineModel_EngineStar_RotaSpeed = [100	1000	4792	4830	5110	5120	5130	5144	5154	5184	5190	5204	5242	5298	5300	5308	5324	5350	5388	5430	5478	5534	5590	5650	5710	5776	5844	5910	5978	6054	6134	6212	6286	6362	6440	6522	6606	6694	6776	6902	6956	7044	7138	7222	7320	7414	7506	7602	7704	7806	7902	8000	8098	8200	8304	8408	8520	8630	8742	8864	8980	9090	9204	9314	9442	9560	9666	9784	9900	10016	10148	10272	10400	10532	10672	10800	11098	11192	11284	11448	11538	11692	11854	12020	12192	12358	12544	12724	12924	13118	13334	13536	13730	13960	14164	14402	14636	14864	15104	15350	15602	15890	16186	16474	16774	17096	17400	17772	18102	18414	18782	19174	19608	20032	20492	20962	21486	22032	22628	23510	23880	24526	25228	25946	26758	27588	28490]*2;
PL_EngineModel_EngineStar_Temp_Exhaust = [128	129	129.1	130	131	131.1	132	133	134	134.1	135	135.1	136	136.1	137	137.1	138	139	139.1	140	141	143	144	146	148	149	151	154	156	160	164	168	173	178	183	188	194	200	207	214	218	224	231	237	243	250	256	263	269	276	282	289	295	302	309	316	323	329	334	339	344	348	351	354	357	360	362	365	368	370	373	375	378	380	382	384	387	389	392	395	396	400	403	406	409	412	415	418	421	425	429	433	437	441	445	448	452	456	460	464	468	472	477	482	487	493	500	507	513	519	526	532	539	547	557	568	580	593	607	623	632	648	663	677	690	702	712];
PL_EngineModel_EngineStar_Press_P2 = [1.013	1.0984	1.099144828	1.099931034	1.103613793	1.162662069	1.143793103	1.131006897	1.123186207	1.1176	1.114	1.111806897	1.110524138	1.10982069	1.109655172	1.10982069	1.110151724	1.110689655	1.111475862	1.112344828	1.113337931	1.114496552	1.115655172	1.116896552	1.118137931	1.119503448	1.120910345	1.122275862	1.123682759	1.125255172	1.126910345	1.128524138	1.130055172	1.131627586	1.133241379	1.134937931	1.136675862	1.138496552	1.140193103	1.1428	1.143917241	1.145737931	1.147682759	1.14942069	1.151448276	1.153393103	1.155296552	1.157282759	1.159393103	1.161503448	1.163489655	1.165517241	1.167544828	1.169655172	1.171806897	1.173958621	1.176275862	1.178551724	1.180868966	1.183393103	1.185793103	1.188068966	1.190427586	1.192703448	1.195351724	1.197793103	1.199986207	1.202427586	1.204827586	1.207227586	1.209958621	1.212524138	1.215172414	1.217903448	1.2208	1.223448276	1.229613793	1.231558621	1.233462069	1.236855172	1.238717241	1.241903448	1.245255172	1.248689655	1.252248276	1.255682759	1.259531034	1.263255172	1.267393103	1.271406897	1.275875862	1.280055172	1.284068966	1.288827586	1.293048276	1.297972414	1.302813793	1.307531034	1.312496552	1.317586207	1.3228	1.328758621	1.334882759	1.340841379	1.347048276	1.353710345	1.36	1.367696552	1.374524138	1.38097931	1.388593103	1.396703448	1.405682759	1.414455172	1.423972414	1.433696552	1.444537931	1.455834483	1.468165517	1.486413793	1.494068966	1.507434483	1.521958621	1.536813793	1.553613793	1.570786207	1.589448276]*1000;

PL_EngineModel_IdleAbove_Ter = [0.4184 0.4184 0.4184 0.3024 0.2324 0.2184 0.197 0.2347 0.1589 0.2394 0.1341 0.3087 0.1910 0.1910]*1.0142;
PL_EngineModel_IdleAbove_Nr = [0 21 60.566 66.799 71.721 75.770 79.569 82.671 85.436 87.693 87.930 89.917 92.099 103]*1.0142;

PL_EngineModel_IdleAbove_Wfr = [0 10 23.5 27.5 31.5 35.5 39.5 43.5 47.5 51.5 52 56 60 80]*1.0142;
PL_EngineModel_IdleAbove_Tempr = [15 300 457 458 467 483 497 521 547 569 569 598 628 720]/279.85;
PL_EngineModel_IdleAbove_P2r = [1 1.6 1.84 2.02 2.26 2.47 2.69 2.88 3.08 3.23 3.3 3.44 3.55 4.1]*100/101.325;
