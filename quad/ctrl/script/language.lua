-- language.lua
-- language implements

Lang = { Eng = 1, Chn = 2}
Lang[Lang.Eng] = {
    ["Title"] = "Quad Flight Monitor",
}
Lang[Lang.Chn] = {
    ["Title"] = "��������",
    ["Open"] = "��",
    ["Send"] = "����",
    ["Close"] = "�ر�",
    ["Clear"] = "���",
    ["Refresh"] = "ˢ��",
    ["Pitch"] = "����",
    ["Roll"] = "���",
    ["Yaw"] = "ƫ��",
    ["Motor"] = "���",
    ["exeTime"] = "ִ��ʱ��",
    ["Thro"] = "����",
    ["Preview"] = "Ԥ��",
    ["Angle"] = "�Ƕ�",
    ["Attitude Data"] = "��̬����",
    ["Parame Set"] = "��������",
    ["Quad Set"] = "��������",
    ["Motor Set"] = "�������",
    ["Set"] = "����",
    ["Gyro"] = "���ٶ�",
    ["Acc"] = "���ٶ�",
    ["Mag"] = "�ų�",
    ["Sensor"] = "������",
    ["Sensor Data"] = "����������",
    ["Save"] = "����",
    ["Load"] = "����",
}

-- set current language
Lang.current = Lang.Chn
function loadStr(id)
    return Lang[Lang.current][id] or Lang[Lang.Eng][id] or id
end
