--script.lua
--lua�еĵ���ע�ͣ�������-��ͷ��һַ�����еĽ�β����C/C++�е�//ע��һ��
--[[
�����lua�еĶ���ע��
������"-"������"["��ͷ��������"]"��β����C/C++�е� /* �� */һ��
]]
-- ����һ������log��������һ������ v
-- ���������������log��Ϣ�Ĳ�����������������ֿ����Զ�ת�����ַ�
function log(v)
    logEdit:append(tostring(v))
end
dofile("quadmonitor.lua")
mdiArea:addSubWindow( QuadMonitor()  ):show()
