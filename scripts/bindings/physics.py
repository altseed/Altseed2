from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

Collider = cbg.Class('Altseed', 'Collider')
with Collider as class_:
    with class_.add_constructor() as func_:
        func_.is_public = False
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コライダの親クラス')
    with class_.add_property(Vector2F, 'Position') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'コライダの位置情報を取得・設定します。')
    with class_.add_property(float, 'Rotation') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'コライダの回転情報を取得・設定します。')
    with class_.add_func('GetIsCollided') as func_:
        func_.add_arg(Collider, 'collider')
        func_.return_value.type_ = bool
        func_.brief = cbg.Description()
        func.brief.add('ja', '指定したコライダとの衝突判定を行います。')

CircleCollider = cbg.Class('Altseed', 'CircleCollider')
with CircleCollider as class_:
    class_.add_constructor()
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '円形コライダのクラス')
    with class_.add_property(float, 'Radius') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '円形コライダの半径を取得・設定します。')
    with class_.add_func('GetIsCollided') as func_:
        func_.add_arg(Collider, 'collider')
        func_.return_value.type_ = bool
        func_.brief = cbg.Description()
        func.brief.add('ja', '指定したコライダとの衝突判定を行います。')

RectangleCollider = cbg.Class('Altseed', 'RectangleCollider')
with RectangleCollider as class_:
    class_.add_constructor()
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '矩形コライダのクラス')
    with class_.add_property(Vector2F, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '矩形コライダの幅・高さを取得・設定します。')
    with class_.add_property(Vector2F, 'CenterPosition') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '矩形コライダの中心の位置を取得・設定します。')
    with class_.add_func('GetIsCollided') as func_:
        func_.add_arg(Collider, 'collider')
        func_.return_value.type_ = bool
        func_.brief = cbg.Description()
        func.brief.add('ja', '指定したコライダとの衝突判定を行います。')

PolygonCollider = cbg.Class('Altseed', 'PolygonCollider')
with PolygonCollider as class_:
    class_.add_constructor()
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '多角形コライダのクラス')
    with class_.add_property(Vector2FArray, 'Vertexes') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '多角形コライダの頂点の座標を取得・設定します。')
    with class_.add_func('GetIsCollided') as func_:
        func_.add_arg(Collider, 'collider')
        func_.return_value.type_ = bool
        func_.brief = cbg.Description()
        func.brief.add('ja', '指定したコライダとの衝突判定を行います。')
