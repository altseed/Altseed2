from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

Collider = cbg.Class('Altseed2', 'Collider')
with Collider as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コライダの抽象基本クラスです')
    class_.SerializeType = cbg.SerializeType.Interface

    with class_.add_property(Vector2F, 'Position') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.is_public = True
        prop_.serialized = False
        prop_.onlyExtern = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'コライダの位置情報を取得または設定します。')

    with class_.add_property(float, 'Rotation') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.is_public = True
        prop_.serialized = False
        prop_.onlyExtern = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'コライダの回転情報を取得または設定します。')

    with class_.add_property(Matrix44F, 'Transform') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.is_public = True
        prop_.onlyExtern = True
        prop_.serialized = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '変形行列を取得または設定します。')
        
    with class_.add_func('GetIsCollidedWith') as func_:
        func_.add_arg(Collider, 'collider')
        func_.return_value.type_ = bool
        func_.is_public = True
        func_.brief = cbg.Description()
        func_.brief.add('ja', '指定したコライダとの衝突判定を行います。')

CircleCollider = cbg.Class('Altseed2', 'CircleCollider')
with CircleCollider as class_:
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '円形コライダのクラス')
    class_.SerializeType = cbg.SerializeType.Interface_Usebase

    with class_.add_func('Create') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('ja', '円形コライダを作成します。')
        func_.is_static = True
        func_.is_public = True
        func_.return_value.type_ = CircleCollider

    with class_.add_property(float, 'Radius') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.serialized = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '円形コライダの半径を取得または設定します。')

RectangleCollider = cbg.Class('Altseed2', 'RectangleCollider')
with RectangleCollider as class_:
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '矩形コライダのクラス')
    class_.SerializeType = cbg.SerializeType.Interface_Usebase

    with class_.add_func('Create') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('ja', '矩形コライダを作成します。')
        func_.is_static = True
        func_.is_public = True
        func_.return_value.type_ = RectangleCollider
    
    with class_.add_property(Vector2F, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.serialized = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '矩形コライダの幅・高さを取得または設定します。')
    with class_.add_property(Vector2F, 'CenterPosition') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.serialized = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '矩形コライダの中心の位置を取得または設定します。')

PolygonCollider = cbg.Class('Altseed2', 'PolygonCollider')
with PolygonCollider as class_:
    class_.base_class = Collider
    class_.brief = cbg.Description()
    class_.brief.add('ja', '多角形コライダのクラス')
    class_.SerializeType = cbg.SerializeType.Interface_Usebase

    with class_.add_func('Create') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('ja', '多角形コライダを作成します。')
        func_.is_static = True
        func_.is_public = True
        func_.return_value.type_ = PolygonCollider
    
    with class_.add_property(Vector2FArray, 'Vertexes') as prop_:
        prop_.is_public = False
        prop_.has_getter = True
        prop_.has_setter = True
        prop_.onlyExtern = True
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '多角形コライダの頂点の座標を取得または設定します')