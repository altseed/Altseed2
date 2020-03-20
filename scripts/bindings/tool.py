from . import CppBindingGenerator as cbg
import ctypes
from .math import Vector2F, Vector4F

ToolDir = cbg.Enum('Altseed', 'ToolDir')
with ToolDir as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ImGuiで使用する方向')

    enum_.add('None', -1)
    with enum_.add('Left', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左方向')
    with enum_.add('Right', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右方向')
    with enum_.add('Up', 2) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '上方向')
    with enum_.add('Down', 3) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '下方向')

ToolCond = cbg.Enum('Altseed', 'ToolCond')
with ToolCond as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add(
        'en', 'Do NOT combine multiple values using binary operators')
    enum_.brief.add('ja', 'バイナリ演算子を使用して複数の値を結合しないでください')

    enum_.add('None', 0)

    with enum_.add('Always', 1 << 0) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Set the variable always')
        v.brief.add('ja', '常に変数を設定します')

    with enum_.add('Once', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Set the variable once per runtime session (only the first call with succeed)')
        v.brief.add('ja', 'ランタイムセッションごとに変数を1回設定します（成功した最初の呼び出しのみ）')

    with enum_.add('FirstUseEver', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Set the variable if the object/window has no persistently saved data (no entry in .ini file)')
        v.brief.add(
            'ja', 'オブジェクト/ウィンドウに永続的に保存されたデータがない場合（.iniファイルにエントリがない場合）、変数を設定します')

    with enum_.add('Appearing', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Set the variable if the object/window is appearing after being hidden/inactive (or the first time)')
        v.brief.add(
            'ja', 'オブジェクト/ウィンドウが非表示/非アクティブになった後（または初めて）表示される場合は、変数を設定します')

ToolTreeNode = cbg.Enum('Altseed', 'ToolTreeNode')
with ToolTreeNode as enum_:
    enum_.add('None', 0)
    with enum_.add('Selected', 1 << 0) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Draw as selected')
        v.brief.add('ja', 'Draw as selected')

    with enum_.add('Framed', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Full colored frame (e.g. for CollapsingHeader)')

    with enum_.add('AllowItemOverlap', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Hit testing to allow subsequent widgets to overlap this one')

    with enum_.add('NoTreePushOnOpen', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Don\'t do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack')

    with enum_.add('NoAutoOpenOnLog', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Don\'t automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)')

    with enum_.add('DefaultOpen', 1 << 5) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Default node to be open')

    with enum_.add('OpenOnDoubleClick', 1 << 6) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Need double-click to open node')

    with enum_.add('OpenOnArrow', 1 << 7) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.')

    with enum_.add('Leaf', 1 << 8) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'No collapsing, no arrow (use as a convenience for leaf nodes).')

    with enum_.add('Bullet', 1 << 9) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Display a bullet instead of arrow')

    with enum_.add('FramePadding', 1 << 10) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().')

    with enum_.add('SpanAvailWidth', 1 << 11) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line. In the future we may refactor the hit system to be front-to-back, allowing natural overlaps and then this can become the default.')

    with enum_.add('SpanFullWidth', 1 << 12) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Extend hit box to the left-most and right-most edges (bypass the indented area).')

    with enum_.add('NavLeftJumpsBackHere', 1 << 13) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '(WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)')

    enum_.add('CollapsingHeader', (1 << 1) | (1 << 3) | (1 << 4))

ToolInputText = cbg.Enum('Altseed', 'ToolInputText')
with ToolInputText as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'Toolにおいてインプットされるテキストの設定を表します')

    enum_.add('None', 0)

    with enum_.add('CharsDecimal', 1 << 0) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Allow 0123456789.+-*/')
        v.brief.add('ja', '0123456789.+-*/ を許可します。')

    with enum_.add('CharsHexadecimal', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Allow 0123456789ABCDEFabcdef')
        v.brief.add('ja', '0123456789ABCDEFabcdef を許可します')

    with enum_.add('CharsUppercase', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Turn a..z into A..Z')
        v.brief.add('ja', 'a..z を A..Z に変換します')

    with enum_.add('CharsNoBlank', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Filter out spaces, tabs')
        v.brief.add('ja', 'スペースとタブを除外します')

    with enum_.add('AutoSelectAll', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Select entire text when first taking mouse focus')
        v.brief.add('ja', '最初にマウスフォーカスしたときにテキスト全体を選択します')

    with enum_.add('EnterReturnsTrue', 1 << 5) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Return \'true\' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the `IsItemDeactivatedAfterEdit()` function.')
        v.brief.add(
            'ja', '（値が変更されるたびにではなく）Enterが押されたときに `true` を返します。 `IsItemDeactivatedAfterEdit()` 関数を調べることを検討してください。')

    with enum_.add('CallbackCompletion', 1 << 6) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Callback on pressing TAB (for completion handling)')
        v.brief.add('ja', 'Tabキーを押したときのコールバック（完了処理のため）')

    with enum_.add('CallbackHistory', 1 << 7) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Callback on pressing Up/Down arrows (for history handling)')
        v.brief.add('ja', '上下矢印を押すとコールバック（履歴処理用）')

    with enum_.add('CallbackAlways', 1 << 8) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Callback on each iteration. User code may query cursor position, modify text buffer.')
        v.brief.add('ja', '各反復でのコールバック。 ユーザーコードは、カーソル位置を照会し、テキストバッファーを変更できます。')

    with enum_.add('CallbackCharFilter', 1 << 9) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Callback on character inputs to replace or discard them. Modify \'EventChar\' to replace or discard, or return 1 in callback to discard.')
        v.brief.add(
            'ja', '置換または破棄する文字入力のコールバック。 \'EventChar\'を変更して置換または破棄するか、コールバックで1を返して破棄します。')

    with enum_.add('AllowTabInput', 1 << 10) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Pressing TAB input a \'\\t\' character into the text field')
        v.brief.add('ja', 'Tabキーを押すと、テキストフィールドに\'\\t\'という文字が入力されます。')

    with enum_.add('CtrlEnterForNewLine', 1 << 11) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).')
        v.brief.add(
            'ja', '複数行モードでは、Enterでフォーカスを外し、Ctrl + Enterで新しい行を追加します（デフォルトは反対です：Ctrl + Enterでフォーカスを外し、Enterで行を追加します）。')

    with enum_.add('NoHorizontalScroll', 1 << 12) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable following the cursor horizontally')
        v.brief.add('ja', 'カーソルの水平方向のフォローを無効にする')

    with enum_.add('AlwaysInsertMode', 1 << 13) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Insert mode')
        v.brief.add('ja', 'インサートモード')

    with enum_.add('ReadOnly', 1 << 14) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Read-only mode')
        v.brief.add('ja', '読み取り専用モード')

    with enum_.add('Password', 1 << 15) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Password mode, display all characters as \'*\'')
        v.brief.add('ja', 'パスワードモード。すべての文字を\'*\'として表示します。')

    with enum_.add('NoUndoRedo', 1 << 16) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().')
        v.brief.add(
            'ja', '元に戻す/やり直しを無効にします。 アクティブな間は入力テキストがテキストデータを所有していることに注意してください。独自の元に戻す/やり直しスタックを提供する場合は、たとえば ClearActiveID（）を呼び出します。')

    with enum_.add('CharsScientific', 1 << 17) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Allow 0123456789.+-*/eE (Scientific notation input)')
        v.brief.add('ja', '0123456789.+-*/eE (科学表記法の入力) を許可します')

    with enum_.add('CallbackResize', 1 << 18) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Callback on buffer capacity changes request (beyond \'buf_size\' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it.')
        v.brief.add('ja', 'バッファ容量のコールバックはリクエストを変更し（\'buf_size \'パラメータ値を超えて）、文字列が大きくなります。 文字列のサイズを変更する必要がある場合に通知します（サイズのキャッシュを保持する文字列タイプの場合）。 コールバックで新しいBufSizeが提供され、それを尊重する必要があります。')

ToolColorEdit = cbg.Enum('Altseed', 'ToolColorEdit')
with ToolColorEdit as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'Toolにおける色の設定を表します')

    enum_.add('None', 0)

    with enum_.add('NoAlpha', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker, ColorButton`: ignore Alpha component (will only read 3 components from the input pointer).')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: Alphaコンポーネントを無視します（入力ポインターから3つのコンポーネントのみを読み取ります）。')

    with enum_.add('NoPicker', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit`: disable picker when clicking on colored square.')
        v.brief.add('ja', '`ColorEdit`: 色付きの正方形をクリックしたときにピッカーを無効にします。')

    with enum_.add('NoOptions', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit`: disable toggling options menu when right-clicking on inputs/small preview.')
        v.brief.add(
            'ja', '`ColorEdit`: 入力/小さなプレビューを右クリックしたときのオプションメニューの切り替えを無効にします。')

    with enum_.add('NoSmallPreview', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker`: disable colored square preview next to the inputs. (e.g. to show only the inputs)')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker`: 入力の横にある色付きの正方形プレビューを無効にします。 （例：入力のみを表示する）')

    with enum_.add('NoInputs', 1 << 5) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker`: disable inputs sliders/text widgets (e.g. to show only the small preview colored square).')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker: 入力スライダー/テキストウィジェットを無効にします（たとえば、小さなプレビューの色付きの四角形のみを表示します）。')

    with enum_.add('NoTooltip', 1 << 6) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker, ColorButton`: disable tooltip when hovering the preview.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: プレビューをホバーするときにツールチップを無効にします。')

    with enum_.add('NoLabel', 1 << 7) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker`: インラインテキストラベルの表示を無効にします（ラベルは引き続きツールチップとピッカーに転送されます）。')

    with enum_.add('NoSidePreview', 1 << 8) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorPicker` : disable bigger color preview on right side of the picker, use small colored square preview instead.')
        v.brief.add(
            'ja', '`ColorPicker`: ピッカーの右側の大きなカラープレビューを無効にし、代わりに小さな色付きの正方形プレビューを使用します。')

    with enum_.add('NoDragDrop', 1 << 9) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit`: disable drag and drop target. `ColorButton`: disable drag and drop source.')
        v.brief.add(
            'ja', '`ColorEdit`: ドラッグアンドドロップターゲットを無効にします。 `ColorButton`: ドラッグアンドドロップソースを無効にします。')

    with enum_.add('AlphaBar', 1 << 16) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker`: show vertical alpha bar/gradient in picker.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker`: ピッカーに垂直アルファバー/グラデーションを表示します。')

    with enum_.add('AlphaPreview', 1 << 17) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker, ColorButton`: display preview as a transparent color over a checkerboard, instead of opaque.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: プレビューを不透明ではなく、チェッカーボード上の透明色として表示します。')

    with enum_.add('AlphaPreviewHalf', 1 << 18) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker, ColorButton`: display half opaque / half checkerboard, instead of opaque.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: 不透明ではなく、半不透明/半市松模様を表示します。')

    with enum_.add('HDR', 1 << 19) as v:
        v.brief = cbg.Description()
        v.brief.add('en', '`(WIP) ColorEdit`: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use Float flag as well).')
        v.brief.add(
            'ja', '`(WIP) ColorEdit`: 現在、RGBAエディションで0.0f..1.0fの制限のみを無効にします（注：おそらくFloatフラグも使用したいでしょう）。')

    with enum_.add('DisplayRGB', 1 << 20) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit`: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.')
        v.brief.add(
            'ja', '`ColorEdit`: RGB/HSV/Hexの_display_タイプをオーバーライドします。 `ColorPicker`: 1つ以上のRGB/HSV/Hexを使用して任意の組み合わせを選択します。')

    with enum_.add('DisplayHSV', 1 << 21) as v:
        v.brief = cbg.Description()
        v.brief.add('en', '')
        v.brief.add('ja', '')

    with enum_.add('DisplayHex', 1 << 22) as v:
        v.brief = cbg.Description()
        v.brief.add('en', '')
        v.brief.add('ja', '')

    with enum_.add('Uint8', 1 << 23) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker, ColorButton`: _display_ values formatted as 0..255.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: 0..255としてフォーマットされた_display_値。')

    with enum_.add('Float', 1 << 24) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.')
        v.brief.add(
            'ja', '`ColorEdit, ColorPicker, ColorButton`: _display_値は、0..255整数ではなく0.0f..1.0f浮動小数点としてフォーマットされます。 整数による値の往復はありません。')

    with enum_.add('PickerHueBar', 1 << 25) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'ColorPicker: bar for Hue, rectangle for Sat/Value.')
        v.brief.add('ja', '`ColorPicker`: Hueのバー、Sat/Valueの長方形。')

    with enum_.add('PickerHueWheel', 1 << 26) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorPicker`: wheel for Hue, triangle for Sat/Value.')
        v.brief.add('ja', '`ColorPicker`: Hueのホイール、Sat/Valueの三角形。')

    with enum_.add('InputRGB', 1 << 27) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '`ColorEdit, ColorPicker`: input and output data in RGB format.')
        v.brief.add('ja', '`ColorEdit, ColorPicker`: RGB形式の入出力データ')

    with enum_.add('InputHSV', 1 << 28) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'ColorEdit, ColorPicker: input and output data in HSV format.')
        v.brief.add('ja', '`ColorEdit, ColorPicker`: HSV形式の入力および出力データ。')

    with enum_.add('OptionsDefault', (1 << 23) | (1 << 20) | (1 << 27) | (1 << 25)) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Defaults Options. You can set application defaults using SetColorEditOptions(). The intent is that you probably don\'t want to override them in most of your calls. Let the user choose via the option menu and/or call SetColorEditOptions() once during startup.')
        v.brief.add('ja', 'デフォルトオプション。 `SetColorEditOptions()` を使用して、アプリケーションのデフォルトを設定できます。 意図はおそらくあなたの呼び出しのほとんどでそれらをオーバーライドしたくないことです。 ユーザーがオプションメニューから選択できるようにするか、起動時に`SetColorEditOptions()`を1回呼び出します。')

ToolSelectable = cbg.Enum('Altseed', 'ToolSelectable')
with ToolSelectable as enum_:
    with enum_.add('None', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('en', '')
        v.brief.add('ja', '')

    with enum_.add('DontClosePopups', 1 << 0) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Clicking this don\'t close parent popup window')
        v.brief.add('ja', 'このボタンをクリックしても、親ポップアップウィンドウは閉じません')

    with enum_.add('SpanAllColumns', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Selectable frame can span all columns (text will still fit in current column)')
        v.brief.add('ja', '選択可能なフレームはすべての列にまたがることができます（テキストは現在の列に収まります）')

    with enum_.add('AllowDoubleClick', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Generate press events on double clicks too')
        v.brief.add('ja', 'ダブルクリックした場合もプレスイベントを生成')

    with enum_.add('Disabled', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Cannot be selected, display grayed out text')
        v.brief.add('ja', '選択できません、グレー表示されたテキストを表示します')

    with enum_.add('AllowItemOverlap', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', '(WIP) Hit testing to allow subsequent widgets to overlap this one')
        v.brief.add('ja', '(WIP) ヒットテストにより、後続のウィジェットがこのウィジェットとオーバーラップできるようにします')

ToolWindow = cbg.Enum('Altseed', 'ToolWindow')
with ToolWindow as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'Toolのウィンドウにおける設定を表します')

    enum_.add('None', 0)

    _NoTitleBar = 1 << 0
    with enum_.add('NoTitleBar', _NoTitleBar) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable title-bar')
        v.brief.add('ja', 'タイトルバーを無効にする')

    _NoResize = 1 << 1
    with enum_.add('NoResize', _NoResize) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable user resizing with the lower-right grip')
        v.brief.add('ja', '右下のグリップを使ったユーザーのサイズ変更を無効にします')

    with enum_.add('NoMove', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable user moving the window')
        v.brief.add('ja', 'ユーザーがウィンドウを移動できないようにする')

    _NoScrollbar = 1 << 3
    with enum_.add('NoScrollbar', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable scrollbars (window can still scroll with mouse or programmatically)')
        v.brief.add('ja', 'スクロールバーを無効にします（ウィンドウはマウスまたはプログラムでスクロールできます）')

    with enum_.add('NoScrollWithMouse', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.')
        v.brief.add(
            'ja', 'ユーザーがマウスホイールで垂直にスクロールできないようにします。 子ウィンドウでは、NoScrollbarも設定されていない限り、マウスホイールは親に転送されます。')

    _NoCollapse = 1 << 5
    with enum_.add('NoCollapse', _NoCollapse) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable user collapsing window by double-clicking on it')
        v.brief.add('ja', 'ユーザー折りたたみウィンドウをダブルクリックして無効にします')

    with enum_.add('AlwaysAutoResize', 1 << 6) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Resize every window to its content every frame')
        v.brief.add('ja', 'フレームごとにコンテンツごとにウィンドウのサイズを変更します')

    with enum_.add('NoBackground', 1 << 7) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).')
        v.brief.add(
            'ja', '描画背景色(`WindowBg`など)および外枠を無効にします。 `SetNextWindowBgAlpha(0.0f)`を使用する場合と同様です。')

    with enum_.add('NoSavedSettings', 1 << 8) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Never load/save settings in .ini file')
        v.brief.add('ja', '.iniファイルの設定をロード/保存しない')

    _NoMouseInputs = 1 << 9
    with enum_.add('NoMouseInputs', _NoMouseInputs) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable catching mouse, hovering test with pass through.')
        v.brief.add('ja', 'パススルーでテストをホバリング、キャッチマウスを無効にします。')

    with enum_.add('MenuBar', 1 << 10) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Has a menu-bar')
        v.brief.add('ja', 'メニューバーがあります')

    with enum_.add('HorizontalScrollbar', 1 << 11) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Allow horizontal scrollbar to appear (off by default). You may use `SetNextWindowContentSize(Vector2F(width,0.0f));` prior to calling Begin() to specify width. ')
        v.brief.add(
            'ja', '水平スクロールバーの表示を許可します（デフォルトではオフ）。 `Begin()`を呼び出す前に、`SetNextWindowContentSize(Vector2F(width, 0.0f));`を使用して幅を指定できます。')

    with enum_.add('NoFocusOnAppearing', 1 << 12) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable taking focus when transitioning from hidden to visible state')
        v.brief.add('ja', '非表示から表示状態に移行するときにフォーカスを取得できないようにします')

    with enum_.add('NoBringToFrontOnFocus', 1 << 13) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)')
        v.brief.add(
            'ja', 'フォーカスを取得するときにウィンドウを前面に移動することを無効にします（たとえば、クリックするか、プログラムでフォーカスを与える）')

    with enum_.add('AlwaysVerticalScrollbar', 1 << 14) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Always show vertical scrollbar (even if `ContentSize.Y < Size.Y`)')
        v.brief.add('ja', '常に垂直スクロールバーを表示します（`ContentSize.Y < Size.Y`の場合でも）')

    with enum_.add('AlwaysHorizontalScrollbar', 1 << 15) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Always show horizontal scrollbar (even if `ContentSize.x < Size.x`)')
        v.brief.add('ja', '常に水平スクロールバーを表示します（`ContentSize.x < Size.x`であっても）')

    with enum_.add('AlwaysUseWindowPadding', 1 << 16) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)')
        v.brief.add(
            'ja', '境界線のない子ウィンドウが`style.WindowPadding`を使用するようにします（境界線のない子ウィンドウではデフォルトで無視されるため、より便利です）')

    _NoNavInputs = 1 << 18
    with enum_.add('NoNavInputs', _NoNavInputs) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'No gamepad/keyboard navigation within the window')
        v.brief.add('ja', 'ウィンドウ内にゲームパッド/キーボードナビゲーションはありません')

    _NoNavFocus = 1 << 19
    with enum_.add('NoNavFocus', _NoNavFocus) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)')
        v.brief.add(
            'ja', 'ゲームパッド/キーボードナビゲーションでこのウィンドウにフォーカスしない（たとえば、CTRL + TABでスキップ）')

    with enum_.add('UnsavedDocument', 1 << 20) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Append \'*\' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup, etc.) without flicker.')
        v.brief.add('ja', '###演算子の使用を避けるために、IDに影響を与えずにタイトルに\'*\'を追加します。 タブ/ドッキングコンテキストで使用する場合、クロージャーでタブが選択され、クロージャーは1フレーム延期され、コードがちらつきなしに（確認ポップアップなどを使用して）クロージャーをキャンセルできるようにします。')

    enum_.add('NoNav', _NoNavInputs | _NoNavFocus)

    enum_.add('NoDecoration', _NoTitleBar |
              _NoResize | _NoScrollbar | _NoCollapse)

    enum_.add('NoInputs', _NoMouseInputs | _NoNavInputs | _NoNavFocus)

ToolTabBar = cbg.Enum('Altseed', 'ToolTabBar')
with ToolTabBar as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'Toolのタブバーにおける設定を表します')

    enum_.add('None', 0)
    with enum_.add('Reorderable', 1 << 0) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Allow manually dragging tabs to re-order them + New tabs are appended at the end of list')
        v.brief.add('ja', 'タブを手動でドラッグして並べ替えることができます+リストの最後に新しいタブが追加されます')

    with enum_.add('AutoSelectNewTabs', 1 << 1) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Automatically select new tabs when they appear')
        v.brief.add('ja', '新しいタブが表示されたら自動的に選択する')

    with enum_.add('TabListPopupButton', 1 << 2) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable buttons to open the tab list popup')
        v.brief.add('ja', 'ボタンを無効にしてタブリストポップアップを開きます')

    with enum_.add('NoCloseWithMiddleMouseButton', 1 << 3) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user\'s side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.')
        v.brief.add('ja', 'マウスの中ボタンでタブを閉じる（p_open！= NULLで送信される）動作を無効にします。 `if（IsItemHovered（）&& IsMouseClicked（2））* p_open = false`を使用すると、ユーザー側でこの動作を再現できます。')

    with enum_.add('NoTabListScrollingButtons', 1 << 4) as v:
        v.brief = cbg.Description()
        v.brief.add(
            'en', 'Disable scrolling buttons (apply when fitting policy is FittingPolicyScroll)')
        v.brief.add(
            'ja', 'スクロールボタンを無効にする（フィッティングポリシーが`FittingPolicyScroll`の場合に適用）')

    with enum_.add('NoTooltip', 1 << 5) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Disable tooltips when hovering a tab')
        v.brief.add('ja', 'タブをホバーするときにツールチップを無効にする')

    _FittingPolicyResizeDown = 1 << 6
    with enum_.add('FittingPolicyResizeDown', _FittingPolicyResizeDown) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Resize tabs when they don\'t fit')
        v.brief.add('ja', '収まらないタブのサイズを変更する')

    _FittingPolicyScroll = 1 << 7
    with enum_.add('FittingPolicyScroll', _FittingPolicyScroll) as v:
        v.brief = cbg.Description()
        v.brief.add('en', 'Add scroll buttons when tabs don\'t fit')
        v.brief.add('ja', 'タブが収まらない場合にスクロールボタンを追加する')

    enum_.add('FittingPolicyMask', _FittingPolicyResizeDown |
              _FittingPolicyScroll)
    enum_.add('FittingPolicyDefault', _FittingPolicyResizeDown)


ToolGlyphRanges = cbg.Enum('Altseed', 'ToolGlyphRanges')
with ToolGlyphRanges as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('en', 'Don\'t bit operation')
    enum_.brief.add('ja', 'Tool機能を使ってフォントを読み込む際の範囲を指定します。ビット演算は行わないでください。')

    enum_.add('Default')

    with enum_.add('Cyrillic') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'キリル文字')

    with enum_.add('Japanese') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '日本語')
    with enum_.add('ChineseFull') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '繁体字中国語')
    with enum_.add('ChineseSimplifiedCommon') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '簡体字中国語')
    with enum_.add('Korean') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '韓国語')
    with enum_.add('Thai') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'タイ語')

Tool = cbg.Class('Altseed', 'Tool')
with Tool as class_:

    with class_.add_func('GetInstance') as func:
        func.is_static = True
        func.is_public = False
        func.return_value.type_ = Tool

    # with class_.add_func('AddFontFromFileTTF') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', 'Load font from path. Packed files are not supported.')
    #     func_.brief.add('ja', 'パスからフォントを読み込みます。パックされたファイルは非対応です。')
    #     func_.add_arg(ctypes.c_wchar_p, 'path')
    #     func_.add_arg(float, 'sizePixels')
    #     func_.add_arg(ToolGlyphRanges, 'ranges')
    #     func_.return_value.type_ = bool

    with class_.add_func('Begin') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `End()`')
        func_.brief.add('ja', '`End()` を呼び出してください。')
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(ToolWindow, 'flags')
        func_.return_value.type_ = bool

    with class_.add_func('End') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('NewFrame') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.is_public = false

    with class_.add_func('Render') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.is_public = false

    with class_.add_func('Dummy') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('Text') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('TextUnformatted') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('TextWrapped') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('TextColored') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector4F, 'color')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('TextDisabled') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('BulletText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('LabelText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('CollapsingHeader') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ToolTreeNode, 'flags')
        func_.return_value.type_ = bool

    with class_.add_func('TreeNode') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.return_value.type_ = bool

    with class_.add_func('TreeNodeEx') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ToolTreeNode, 'flags')
        func_.return_value.type_ = bool

    with class_.add_func('TreePop') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SetNextItemOpen') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(bool, 'isOpen')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('Button') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        func_.return_value.type_ = bool

    with class_.add_func('CheckBox') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(bool, 'isOpen') as arg:
            arg.called_by = cbg.ArgCalledBy.Out
        func_.return_value.type_ = bool

    with class_.add_func('RadioButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'active')
        func_.return_value.type_ = bool

    with class_.add_func('ArrowButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ToolDir, 'dir')
        func_.return_value.type_ = bool

    with class_.add_func('InvisibleButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        func_.return_value.type_ = bool

    # with class_.add_func('Combo') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     func_.add_arg(const char* [], 'items') # TODO
    #     func_.add_arg(int, 'count')
    #     func_.return_value.type_ = bool

    # with class_.add_func('ListBox') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     func_.add_arg(int*, 'current')
    #     func_.add_arg(const char* [], 'items') # TODO
    #     func_.add_arg(int, 'count')
    #     func_.return_value.type_ = bool

    with class_.add_func('Selectable') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(bool, 'selected') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(ToolSelectable, 'flags')
        func_.return_value.type_ = bool

    # with class_.add_func('InputText') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(STRING, 'buf') as arg: # TODO
    #     func_.add_arg(int, 'bufSize')
    #     func_.add_arg(ToolInputText, 'flags')
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputTextWithHint') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     func_.add_arg(ctypes.c_wchar_p, 'hit')
    #     with func_.add_arg(STRING, 'buf') as arg: # TODO
    #     func_.add_arg(int, 'bufSize')
    #     func_.add_arg(ToolInputText, 'flags')
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputTextMultiline') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     ffunc_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(string, 'buf') as arg: # TODO
    #     func_.add_arg(int, 'bufSize')
    #     func_.add_arg(Vector2F, 'size')
    #     func_.add_arg(ToolInputText, 'flags')
    #     func_.return_value.type_ = bool

    with class_.add_func('InputInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(int, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.return_value.type_ = bool

    # with class_.add_func('InputInt2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(IntArray, 'array') as arg: # TODO
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputInt3') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'array') as arg:
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputInt4') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'array') as arg:
    #     func_.return_value.type_ = bool

    with class_.add_func('InputFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(float, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.return_value.type_ = bool

    # with class_.add_func('InputFloat2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputFloat3') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.return_value.type_ = bool

    # with class_.add_func('InputFloat4') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.return_value.type_ = bool

    with class_.add_func('SliderInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(int, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(float, 'speed')
        func_.add_arg(int, 'valueMin')
        func_.add_arg(int, 'valueMax')
        func_.return_value.type_ = bool

    # with class_.add_func('SliderInt2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(int, 'valueMin')
    #     func_.add_arg(int, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('SliderInt3') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(int, 'valueMin')
    #     func_.add_arg(int, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('SliderInt4') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(int, 'valueMin')
    #     func_.add_arg(int, 'valueMax')
    #     func_.return_value.type_ = bool

    with class_.add_func('SliderFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(float, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(float, 'speed')
        func_.add_arg(float, 'valueMin')
        func_.add_arg(float, 'valueMax')
        func_.return_value.type_ = bool

    # with class_.add_func('SliderFloat2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(float, 'valueMin')
    #     func_.add_arg(float, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('SliderFloat3') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(float, 'valueMin')
    #     func_.add_arg(float, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('SliderFloat4') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'array') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(float, 'valueMin')
    #     func_.add_arg(float, 'valueMax')
    #     func_.return_value.type_ = bool

    with class_.add_func('SliderAngle') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(float, 'angle') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.return_value.type_ = bool

    with class_.add_func('VSliderInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        with func_.add_arg(int, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(int, 'valueMin')
        func_.add_arg(int, 'valueMax')
        func_.return_value.type_ = bool

    with class_.add_func('VSliderFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        with func_.add_arg(float, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(float, 'valueMin')
        func_.add_arg(float, 'valueMax')
        func_.return_value.type_ = bool

    with class_.add_func('DragInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(int, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(float, 'speed')
        func_.add_arg(int, 'valueMin')
        func_.add_arg(int, 'valueMax')
        func_.return_value.type_ = bool

    with class_.add_func('DragFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        with func_.add_arg(float, 'value') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.add_arg(float, 'speed')
        func_.add_arg(float, 'valueMin')
        func_.add_arg(float, 'valueMax')
        func_.return_value.type_ = bool

    # with class_.add_func('DragIntRange2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(int, 'currentMin') as arg:
    #     with func_.add_arg(int, 'currentMax') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(int, 'valueMin')
    #     func_.add_arg(int, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('DragFloatRange2') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(float, 'currentMin') as arg:
    #     with func_.add_arg(float, 'currentMax') as arg:
    #     func_.add_arg(float, 'speed')
    #     func_.add_arg(float, 'valueMin')
    #     func_.add_arg(float, 'valueMax')
    #     func_.return_value.type_ = bool

    # with class_.add_func('ColorEdit3') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(Vector4F, 'color') as arg:
    #     func_.add_arg(ToolColorEdit, 'flags')
    #     func_.return_value.type_ = bool

    # with class_.add_func('ColorEdit4') as func_:
    #     func_.brief = cbg.Description()
    #     func_.brief.add('en', '')
    #     func_.brief.add('ja', '')
    #     func_.add_arg(ctypes.c_wchar_p, 'label')
    #     with func_.add_arg(Vector4F, 'color') as arg:
    #     func_.add_arg(ToolColorEdit, 'flags')
    #     func_.return_value.type_ = bool

    with class_.add_func('OpenPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')

    with class_.add_func('BeginPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndPopup()`')
        func_.brief.add('ja', '`EndPopup()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.return_value.type_ = bool

    with class_.add_func('BeginPopupModal') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndPopup()`')
        func_.brief.add('ja', '`EndPopup()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.return_value.type_ = bool

    with class_.add_func('EndPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('BeginChild') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndChild()`')
        func_.brief.add('ja', '`EndChild()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(bool, 'border')
        func_.add_arg(ToolWindow, 'flags')
        func_.return_value.type_ = bool

    with class_.add_func('EndChild') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('BeginMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndMenuBar()`')
        func_.brief.add('ja', '`EndMenuBar()` を呼び出してください')
        func_.return_value.type_ = bool

    with class_.add_func('EndMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('BeginMenu') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndMenu()`')
        func_.brief.add('ja', '`EndMenu()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'enabled')
        func_.return_value.type_ = bool

    with class_.add_func('EndMenu') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('MenuItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'shortcut')
        func_.add_arg(bool, 'selected')
        func_.add_arg(bool, 'enabled')
        func_.return_value.type_ = bool

    with class_.add_func('BeginTabBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndTabBar()`')
        func_.brief.add('ja', '`EndTabBar()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ToolTabBar, 'flags')
        func_.return_value.type_ = bool

    with class_.add_func('EndTabBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('BeginTabItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndTabItem()`')
        func_.brief.add('ja', '`EndTabItem()` を呼び出してください')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.return_value.type_ = bool

    with class_.add_func('EndTabItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('Indent') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('Unindent') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('Separator') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SetTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'text')

    with class_.add_func('BeginTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', 'Call `EndTooltip()`')
        func_.brief.add('ja', '`EndTooltip()` を呼び出してください')

    with class_.add_func('EndTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('NewLine') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SameLine') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('PushTextWrapPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(float, 'wrapLocalPosX')

    with class_.add_func('PopTextWrapPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SetNextItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(float, 'width')

    with class_.add_func('PushItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(float, 'width')

    with class_.add_func('PopItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('PushButtonRepeat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(bool, 'repeat')

    with class_.add_func('PopButtonRepeat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('Columns') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(int, 'count')
        func_.add_arg(bool, 'border')

    with class_.add_func('NextColumn') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('PushID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(int, 'id')

    with class_.add_func('PopID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('IsItemActive') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool

    with class_.add_func('IsItemHovered') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool

    with class_.add_func('SetScrollHere') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SetScrollHereX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('SetScrollHereY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    with class_.add_func('GetTextLineHeight') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float

    with class_.add_func('GetFontSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float

    with class_.add_func('GetWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F

    with class_.add_func('SetWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('IsMousePosValid') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool

    with class_.add_func('IsMouseDragging') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool

    with class_.add_func('IsMouseDoubleClicked') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(int, 'button')
        func_.return_value.type_ = bool

    with class_.add_func('GetMouseDragDelta') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(int, 'button')
        func_.return_value.type_ = Vector2F

    with class_.add_func('ResetMouseDragDelta') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(int, 'button')

    with class_.add_func('SetNextWindowContentSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('SetNextWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('SetNextWindowPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(Vector2F, 'pos')
