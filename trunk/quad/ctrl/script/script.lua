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
-- ��[�ļ�]->[�½�]�˵�������ʱ���ú���
function file_new()
    -- ����һ��QLuaEdit���󣬲��Ҽ��뵽mdiArea��
    editor = QLuaEdit()
    subWindow = mdiArea:addSubWindow( editor )
    subWindow:show()
    -- mdiArea�����������X��������Ԥ�ȶ���õģ�����Ӧ��Qt������QMdiArea������QMdiArea�Ĵ󲿷�����
    -- Ҳ����˵��Qt��QMdiArea���������ӵ�еķ��������ԣ��������϶���
    -- ��������addSubWindow�������һ���Ӵ��ڣ���Qt�����Ĳ�����QWidget��������QLuaEdit���ִ���
    -- QLuaEdit�����Լ�д��һ�����lua�ű��ı༭�������кź��Z������
    -- �����Խ������Ĳ��ּ����Զ���ı�ǩ�������
end
--[[ �� mdiAreaһ��Ԥ����Ļ���mainWindow,logEdit��qApp
mainWindow �������ڣ���ӦQt�е������� QMainWindow
logEdit ����־�����еı༭�򣬶�ӦQt�е������� QTextEdit
qApp  �ǵ�ǰӦ�ó����ʵ������ӦQt�е������� QApplication
lua��û��ָ�������õĸ�������Qt����Ҫ���û�ָ��ĺ�����������ͬ�ķ�ʽ����
]]
-- ��[�ļ�]->[��]�˵�������ʱ���ú���
function file_open()
    -- ��ȡһ�����ļ���
    name = QCommonDlg.getOpenFileName("��Lua�ű��ļ�", "", "Lua�ű�(*.lua);;ȫ���ļ�(*)")
    -- ��ֻ����ʽ���ļ�
    file = io.open(name,"r")
    if file then
        editor = QLuaEdit()   -- ����һ��lua editor
        -- ����QLuaEdit�̳���QTextEdit������������plainText����Ϊ�ļ�����
        editor.plainText = file:read("*a")
        file:close()  -- �ر��ļ�
        editor.windowTitle = name  -- ���ô�������Ϊ�ļ���
        mdiArea:addSubWindow(editor):show() -- ���һ���Ӵ��ڲ���ʾ
    end
end
-- ��[�ļ�]->[���Ϊ]�˵�������ʱ���ú���
function file_save_as()
    -- ȡ�õ�ǰ������Ӵ��ڣ����õ���lua�༭������Qt��ͨ��QMdiArea��currentSubWindow
    -- ���Կ��Եõ���ǰ������Ӵ��ڣ�������ΪQMdiSubWindow��Ҫ�õ��Ӵ����������Ĵ��ڣ�
    -- ��Ҫ������widget����
    editor = mdiArea.currentSubWindow.widget
    path = editor.windowTitle  -- ͨ��windowTitle�õ��ļ���
    -- ��ȡһ�������ļ��������Ե�ǰ���ļ�����Ϊ��ʼ�ļ���
    path = QCommonDlg.getSaveFileName("����Lua�ű��ļ�",path, "Lua�ű�(*.lua);;ȫ���ļ�(*)")
    -- ��д��ʽ������ļ�������ļ���������գ��������򴴽�
    file = io.open(path, "w+")
    if file then
        -- ����������д���ļ�
        file:write(editor.plainText)
        file:close()
        -- �����µĴ��ڱ���Ϊ�ļ���
        editor.windowTitle = path
    end
end
-- ��[�ļ�]->[����]�˵�������ʱ���ú���
function file_save()
    editor = mdiArea.currentSubWindow.widget
    path = editor.windowTitle
    file = io.open(path, "w+")
    if file then
        file:write(editor.plainText)
        file:close()
    else
        -- ����ļ���ʧ�ܣ���ʹ�����Ϊ��ʽ����
        file_save_as()
    end
end
-- ��[�ļ�]->[�ر�]�˵�������ʱ���ú���
function file_close()
    -- �رյ�ǰ����Ĵ���
    mdiArea:closeActiveSubWindow()
end
-- ��[�ļ�]->[�˳�]�˵�������ʱ���ú���
function file_quit()
    -- �ر������ڣ����������Ϊ�������һ�����ڣ�������˳�
    mainWindow:close()
end
-- ��[�ļ�]->[����ǩ����]�˵�������ʱ���ú���
function file_save_tag()
    editor = mdiArea.currentSubWindow.widget
    -- ���������к���"clas"�ı�ǩ����ǩ��ʼΪ"[color=#800080]",����Ϊ"[/color]"
    editor:setTag("clas","[color=#800080]","[/color]")
    editor:setTag("key","[color=#0000FF]","[/color]")
    editor:setTag("quo","[color=#C80000]","[/color]")
    editor:setTag("com","[color=#008000]","[/color]")
    -- ����QApplication��ľ�̬����clipboard���ú�������Ӧ�ó����ȫ�ּ��а����
    -- ΪQClipboard���ͣ��ٵ���ȫ�ּ��а�����setText����
    -- ������ǩ�Ĵ��������а���
    QApplication.clipboard():setText(editor.tagText)
    log("�ӱ�ǩ��Դ�����Ѹ��Ƶ����а���!")
end
--[[
Ԥ����ı�ǩ������
keyword     �ؼ���
user keyword  �û��ؼ��֣�����ͨ��QLuaEdit��addKeyWord�������
block comment ��ע��
line comment ��ע��
double quotation ˫�����ַ���
single quotation �������ַ���
long quotation ���ַ���
class ��
function ����
]]
-- ��[�༭]->[����]�˵�������ʱ���ú���
function edit_run()
    editor = mdiArea.currentSubWindow.widget
    -- ���ر༭���е�lua�ű�����ִ��
    assert(loadstring(editor.plainText))()
end
-- ͨ��menuBar�����õ�mainWindow��menuBar����
-- �Ա��ķ�ʽ��menuBar����Ӳ˵�
menuBar = mainWindow:menuBar(){
    -- ���һ��[�ļ�]�˵�
    QMenu("�ļ�(&F)"){
        -- ���һ�� [�½�]�˵���
        QAction("�½�(&N)"){
            -- ���˲˵������ʱ������file_new����
            -- ���ô˲˵���Ŀ�ݼ�Ϊ"Ctrl+N"
            triggered = file_new, QKeySequence("Ctrl+N"),
        },
        QAction("��(&O)"){
            triggered = file_open, QKeySequence("Ctrl+O"),
        },
        QAction("����(&S)"){
            triggered = file_save, QKeySequence("Ctrl+S"),
        },
        QAction("���Ϊ(&a)"){
            triggered = file_save_as, QKeySequence("Ctrl+Shift+A"),
        },
        QAction("����ǩ����(&t)"){
            triggered = file_save_tag, QKeySequence("Ctrl+T"),
        },
        QAction("�ر�(&C)"){
            triggered = file_close, QKeySequence("Ctrl+Shift+C"),
        },
        QAction(""){
            separator = true
        },
        QAction("�˳�(&Q)"){
            triggered = file_quit, QKeySequence("Ctrl+Shift+Q"),
        }
    },
    --[[ �༭�˵�ʹ����ͨ��ʽ��ӣ�Ч�������ﱻע�͵��Ĵ�����ͬ
    QMenu("�༭(&E)"){
        QAction("����(&R)"){
            triggered = edit_run, QKeySequence("Ctrl+R"),
        },
    }
    ]]
}
--����ͨ��ʽ���һ���༭�˵�
-- �½�һ����Ϊ[�༭]�˵�
editMenu = QMenu("�༭(&E)")
-- �½�һ����Ϊ[����]�Ĳ˵���
editRunAct = QAction("����(&R)")
-- ��[����]�˵����ʱ������edit_run����
editRunAct.triggered = edit_run
-- ����[����]�˵���Ŀ�ݷ�ʽΪ "Ctrl+R"
editRunAct.shortcut = QKeySequence("Ctrl+R")
-- Ϊ[�༭]�˵����һ���˵���
editMenu:addAction(editRunAct)
-- ��[�༭]�˵�����mainWindow��menuBar��
menuBar:addMenu(editMenu)
--����info.lua�ű���ִ��
dofile("info.lua")
dofile("ttt.lua")

