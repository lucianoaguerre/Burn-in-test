//byte   dev_state[100];

void setData(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  if (error) { return; }

  int id = doc["id"];
  bool ledStatus = doc["status"];
  Serial.println(id);
  Serial.println(ledStatus);
}

void getData(AsyncWebSocketClient * client, String request)
{
   String response;
   StaticJsonDocument<1600> jsonDoc;
   jsonDoc["id00"] = dev_state[0];
   jsonDoc["id01"] = dev_state[1];
   jsonDoc["id02"] = dev_state[2];
   jsonDoc["id03"] = dev_state[3];
   jsonDoc["id04"] = dev_state[4];
   jsonDoc["id05"] = dev_state[5];
   jsonDoc["id06"] = dev_state[6];
   jsonDoc["id07"] = dev_state[7];
   jsonDoc["id08"] = dev_state[8];
   jsonDoc["id09"] = dev_state[9];
   
   jsonDoc["id10"] = dev_state[10];
   jsonDoc["id11"] = dev_state[11];
   jsonDoc["id12"] = dev_state[12];
   jsonDoc["id13"] = dev_state[13];
   jsonDoc["id14"] = dev_state[14];
   jsonDoc["id15"] = dev_state[15];
   jsonDoc["id16"] = dev_state[16];
   jsonDoc["id17"] = dev_state[17];
   jsonDoc["id18"] = dev_state[18];
   jsonDoc["id19"] = dev_state[19];
   
   jsonDoc["id20"] = dev_state[20];
   jsonDoc["id21"] = dev_state[21];
   jsonDoc["id22"] = dev_state[22];
   jsonDoc["id23"] = dev_state[23];
   jsonDoc["id24"] = dev_state[24];
   jsonDoc["id25"] = dev_state[25];
   jsonDoc["id26"] = dev_state[26];
   jsonDoc["id27"] = dev_state[27];
   jsonDoc["id28"] = dev_state[28];
   jsonDoc["id29"] = dev_state[29];

   jsonDoc["id30"] = dev_state[30];
   jsonDoc["id31"] = dev_state[31];
   jsonDoc["id32"] = dev_state[32];
   jsonDoc["id33"] = dev_state[33];
   jsonDoc["id34"] = dev_state[34];
   jsonDoc["id35"] = dev_state[35];
   jsonDoc["id36"] = dev_state[36];
   jsonDoc["id37"] = dev_state[37];
   jsonDoc["id38"] = dev_state[38];
   jsonDoc["id39"] = dev_state[39];

   jsonDoc["id40"] = dev_state[40];
   jsonDoc["id41"] = dev_state[41];
   jsonDoc["id42"] = dev_state[42];
   jsonDoc["id43"] = dev_state[43];
   jsonDoc["id44"] = dev_state[44];
   jsonDoc["id45"] = dev_state[45];
   jsonDoc["id46"] = dev_state[46];
   jsonDoc["id47"] = dev_state[47];
   jsonDoc["id48"] = dev_state[48];
   jsonDoc["id49"] = dev_state[49];

   jsonDoc["id50"] = dev_state[50];
   jsonDoc["id51"] = dev_state[51];
   jsonDoc["id52"] = dev_state[52];
   jsonDoc["id53"] = dev_state[53];
   jsonDoc["id54"] = dev_state[54];
   jsonDoc["id55"] = dev_state[55];
   jsonDoc["id56"] = dev_state[56];
   jsonDoc["id57"] = dev_state[57];
   jsonDoc["id58"] = dev_state[58];
   jsonDoc["id59"] = dev_state[59];

   jsonDoc["id60"] = dev_state[60];
   jsonDoc["id61"] = dev_state[61];
   jsonDoc["id62"] = dev_state[62];
   jsonDoc["id63"] = dev_state[63];
   jsonDoc["id64"] = dev_state[64];
   jsonDoc["id65"] = dev_state[65];
   jsonDoc["id66"] = dev_state[66];
   jsonDoc["id67"] = dev_state[67];
   jsonDoc["id68"] = dev_state[68];
   jsonDoc["id69"] = dev_state[69];

   jsonDoc["id70"] = dev_state[70];
   jsonDoc["id71"] = dev_state[71];
   jsonDoc["id72"] = dev_state[72];
   jsonDoc["id73"] = dev_state[73];
   jsonDoc["id74"] = dev_state[74];
   jsonDoc["id75"] = dev_state[75];
   jsonDoc["id76"] = dev_state[76];
   jsonDoc["id77"] = dev_state[77];
   jsonDoc["id78"] = dev_state[78];
   jsonDoc["id79"] = dev_state[79];

   jsonDoc["id80"] = dev_state[80];
   jsonDoc["id81"] = dev_state[81];
   jsonDoc["id82"] = dev_state[82];
   jsonDoc["id83"] = dev_state[83];
   jsonDoc["id84"] = dev_state[84];
   jsonDoc["id85"] = dev_state[85];
   jsonDoc["id86"] = dev_state[86];
   jsonDoc["id87"] = dev_state[87];
   jsonDoc["id88"] = dev_state[88];
   jsonDoc["id89"] = dev_state[89];

   jsonDoc["id90"] = dev_state[90];
   jsonDoc["id91"] = dev_state[91];
   jsonDoc["id92"] = dev_state[92];
   jsonDoc["id93"] = dev_state[93];
   jsonDoc["id94"] = dev_state[94];
   jsonDoc["id95"] = dev_state[95];
   jsonDoc["id96"] = dev_state[96];
   jsonDoc["id97"] = dev_state[97];
   jsonDoc["id98"] = dev_state[98];
   jsonDoc["id99"] = dev_state[99];
      
   serializeJson(jsonDoc, response);
   client->text(response);
   serializeJsonPretty(jsonDoc, Serial);
}
