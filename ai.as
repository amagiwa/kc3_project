void Main(){
    Vec2 va = getNearestBulletVelocity();
    Vec2 vb = subVector(getPlayerPosition(), getNearestBulletPosition());
    float c = crossVector(va,vb);
    if(c>=0){
        movePlayer(-1,0,false);
    }
    else{
        movePlayer(1,0,false);
    }
}
//2つのベクトルの外積を求める
float crossVector(Vec2 vl, Vec2 vr){
    return (vl.x*vr.y-vl.y*vr.x);
}
//2つのベクトルの差を求める
Vec2 subVector(Vec2 vt, Vec2 vf){
    return (vt-vf);
}
//ベクトルの絶対値の2乗を求める
float absSquareVector(Vec2 v){
    return (v.x*v.x+v.y*v.y);
}
