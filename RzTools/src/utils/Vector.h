#pragma once
#include <cmath>


struct Vector2 {
	Vector2() {};
	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float x;
	float y;

	inline bool operator == (const Vector2& A) const
	{
		return x == A.x && y == A.y;
	}

	inline Vector2 operator + (const Vector2& A) const
	{
		return Vector2(x + A.x, y + A.y);
	}

	inline Vector2 operator + (const float A) const
	{
		return Vector2(x + A, y + A);
	}

	inline Vector2 operator * (const float A) const
	{
		return Vector2(x * A, y * A);
	}

	inline Vector2 operator * (const Vector2& A) const
	{
		return Vector2(x * A.x, y * A.y);
	}

	inline Vector2 operator - (const float A) const///????
	{
		return Vector2(A * x, A * y);
	}

	inline Vector2 operator - (const Vector2& A) const
	{
		return Vector2(x - A.x, y - A.y);
	}

	inline Vector2 operator / (const float A) const
	{
		return Vector2(x / A, y / A);
	}

	inline Vector2 operator / (const Vector2& A) const
	{
		return Vector2(x / A.x, y / A.y);
	}

	float length() {
		return sqrt(x * x + y * y);
	}

	float distance(const Vector2& o) {
		return sqrt(pow(x - o.x, 2) + pow(y - o.y, 2));
	}

	Vector2 vscale(const Vector2& s) {
		return Vector2(x * s.x, y * s.y);
	}

	Vector2 scale(float s) {
		return Vector2(x * s, y * s);
	}

	Vector2 normalize() {
		float l = length();
		return Vector2(x / l, y / l);
	}

	Vector2 add(const Vector2& o) {
		return Vector2(x + o.x, y + o.y);
	}

	Vector2 sub(const Vector2& o) {
		return Vector2(x - o.x, y - o.y);
	}

	Vector2 clone() {
		return Vector2(x, y);
	}

	Vector2 abs_() {
		float x_ = x > 0 ? x : -x;
		float y_ = y > 0 ? y : -y;
		return Vector2(x_, y_);
	}

	Vector2 max_(const Vector2& A) {
		float x_ = x > A.x ? x : A.x;
		float y_ = y > A.y ? y : A.y;
		return Vector2(x_, y_);
	}

	Vector2 max_(float A) {
		float x_ = x > A ? x : A;
		float y_ = y > A ? y : A;
		return Vector2(x_, y_);
	}

	static bool intersect(const Vector2& missileCenter, const Vector2& missileCorner, const Vector2& gameObjCenter, float objPlayRadius) {
		Vector2 v = (gameObjCenter - missileCenter).abs_();
		Vector2 h = (missileCorner - missileCenter).abs_();
		Vector2 u = (v - h).max_(0);
		return u.length() <= sqrt(objPlayRadius);
	}
};

struct Vector3 {
	Vector3() {};
	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;

	float length() {
		return sqrt(x * x + y * y + z * z);
	}

	float distance(const Vector3& o) {
		return sqrt(pow(x - o.x, 2) + pow(y - o.y, 2) + pow(z - o.z, 2));
	}

	inline bool operator == (const Vector3& A) const
	{
		return x == A.x && y == A.y && z == A.z;
	}

	inline Vector3 operator + (const Vector3& A) const
	{
		return Vector3(x + A.x, y + A.y, z + A.z);
	}

	inline Vector3 operator + (const float A) const
	{
		return Vector3(x + A, y + A, z + A);
	}

	inline Vector3 operator * (const float A) const
	{
		return Vector3(A * x, A * y, A * z);
	}

	inline Vector3 operator * (const Vector3& A) const
	{
		return Vector3(A.x * x, A.y * y, A.z * z);
	}

	inline Vector3 operator - (const float A) const///???
	{
		return Vector3(A * x, A * y, A * z);
	}

	inline Vector3 operator - (const Vector3& A) const
	{
		return Vector3(x - A.x, y - A.y, z - A.z);
	}

	inline Vector3 operator / (const float A) const
	{
		return Vector3(x / A, y / A, z / A);
	}

	inline Vector3 operator / (const Vector3& A) const
	{
		return Vector3(x / A.x, y / A.y, z / A.z);
	}

	Vector3 rotate_x(float angle) {
		return Vector3(
			x,
			y * cos(angle) - z * sin(angle),
			y * sin(angle) + z * cos(angle)
		);
	}

	Vector3 rotate_y(float angle) {
		return Vector3(
			x * cos(angle) + z * sin(angle),
			y,
			-x * sin(angle) + z * cos(angle)
		);
	}

	Vector3 rotate_z(float angle) {
		return Vector3(
			x * cos(angle) - y * sin(angle),
			x * sin(angle) + y * cos(angle),
			z
		);
	}

	Vector3 vscale(const Vector3& s) {
		return Vector3(x * s.x, y * s.y, z * s.z);
	}

	Vector3 scale(float s) {
		return Vector3(x * s, y * s, z * s);
	}

	Vector3 normalize() {
		float l = length();
		return Vector3(x / l, y / l, z / l);
	}

	Vector3 add(const Vector3& o) {
		return Vector3(x + o.x, y + o.y, z + o.z);
	}

	Vector3 sub(const Vector3& o) {
		return Vector3(x - o.x, y - o.y, z - o.z);
	}

	Vector3 clone() {
		return Vector3(x, y, z);
	}

	Vector3 extend(const Vector3& dir, double distance) {
		return add(dir).scale(distance);
	}

	Vector3 nextPosition(Vector3& navPositon, float distance) {
		float x_ = navPositon.x - x;
		float y_ = navPositon.y - y;
		float z_ = navPositon.z - z;
		float a = sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
		x_ = (x_ / a) * distance + x;
		y_ = (y_ / a) * distance + y;
		z_ = (z_ / a) * distance + z;
		return Vector3(x_, y_, z_);

	}

	Vector3 abs_() {
		float x_ = x > 0 ? x : -x;
		float y_ = y > 0 ? y : -y;
		float z_ = z > 0 ? y : -z;
		return Vector3(x_, y_, z_);
	}

	Vector3 max_(const Vector3& A) {
		float x_ = x > A.x ? x : A.x;
		float y_ = y > A.y ? y : A.y;
		float z_ = z > A.z ? z : A.z;
		return Vector3(x_, y_, z_);
	}

	Vector3 max_(float a) {
		float x_ = x > a ? x : a;
		float y_ = y > a ? y : a;
		float z_ = z > a ? z : a;
		return Vector3(x_, y_, z_);
	}

	static bool intersect(const Vector3& missileCenter, const Vector3& missileCorner, const Vector3& gameObjCenter, float minDistance) {

		Vector3 v = Vector3(gameObjCenter.x, gameObjCenter.y, gameObjCenter.z).sub(missileCenter).abs_();
		Vector3 h = Vector3(missileCorner.x, missileCorner.y, missileCorner.z).sub(missileCenter).abs_();
		//Vector3 h = missileCorner.sub(missileCenter).abs_();
		Vector3 u = (v - h).max_(0.f);
		return (u.x * u.x + u.z * u.z) <= minDistance * minDistance;
	}

	static bool intersect2(Vector3 startPos, Vector3 endPos, Vector3 objPos, float minDistance) {
		float a = startPos.distance(endPos);
		float b = startPos.distance(objPos);
		float c = endPos.distance(objPos);
		float cos_1 = (a * a + c * c - b * b) / (2 * a * c);
		float cos_2 = (a * a + b * b - c * c) / (2 * a * b);
		if (cos_1 < 0 || cos_2 < 0)
			return false;
		float dis = sin(acos(cos_2)) * b;
		return dis < minDistance;

	}
};

struct Vector4 {
	Vector4() {};
	Vector4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	float x;
	float y;
	float z;
	float w;

	float length() {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float distance(const Vector4& o) {
		return sqrt(pow(x - o.x, 2) + pow(y - o.y, 2) + pow(z - o.z, 2) + pow(w - o.w, 2));
	}

	Vector4 vscale(const Vector4& s) {
		return Vector4(x * s.x, y * s.y, z * s.z, w * s.w);
	}

	Vector4 scale(float s) {
		return Vector4(x * s, y * s, z * s, w * s);
	}

	Vector4 normalize() {
		float l = length();
		return Vector4(x / l, y / l, z / l, w / l);
	}

	Vector4 add(const Vector4& o) {
		return Vector4(x + o.x, y + o.y, z + o.z, w + o.w);
	}

	Vector4 sub(const Vector4& o) {
		return Vector4(x - o.x, y - o.y, z - o.z, w - o.w);
	}

	Vector4 clone() {
		return Vector4(x, y, z, w);
	}
};