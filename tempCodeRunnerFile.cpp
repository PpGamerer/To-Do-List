ap<string, string> myMap;
    vector<map<string, string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline;
    ifstream read;

    read.open("data.csv");
    std::getline(read, textline); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline, ","); //แยกตามหัวข้อ ใช้delimiter = ","
    vector<string> row;
    while (std::getline(read, textline)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i), row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap); //ใส่ทุกคู่ลงใน data
    }