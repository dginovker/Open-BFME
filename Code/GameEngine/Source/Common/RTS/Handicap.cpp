// cl: /EHsc
#pragma intrinsic(strlen)
#include <string.h>

typedef float Real;

enum NameKeyType {};

class Dict;
class NameKeyGenerator;
class Handicap;

template <typename T> class StringBase;
template <> class StringBase<char> {
	friend class Handicap;
public:
	struct Header { int ref_count; unsigned short length; unsigned short capacity; char data[1]; };
	void set(const char *str, int len);
	void concat(const char *str, int len);
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
private:
	StringBase() {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
public:
	Header *m_data;
};

class Dict {
public:
	Real getReal(NameKeyType key, bool *exists) const;
};

class NameKeyGenerator {
public:
	NameKeyType nameToKey(const char *s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Handicap {
public:
	enum HandicapType { BUILDCOST, BUILDTIME, HANDICAP_TYPE_COUNT };
	enum ThingType { GENERIC, BUILDINGS, THING_TYPE_COUNT };
	void readFromDict(const Dict *d);
private:
	Real m_handicaps[HANDICAP_TYPE_COUNT][THING_TYPE_COUNT];
};

// ?readFromDict@Handicap@@QAEXPBVDict@@@Z present-unmatched 360/362 bytes, push/store ordering diff
void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[HANDICAP_TYPE_COUNT] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[THING_TYPE_COUNT] =
	{
		"GENERIC",
		"BUILDINGS",
	};

	StringBase<char> c;
	c.m_data = 0;
	const char **ht = htNames;
	const char **tt = ttNames;

	for (int i = 0; i < HANDICAP_TYPE_COUNT; ++i)
	{
		for (int j = 0; j < THING_TYPE_COUNT; ++j)
		{
			c.releaseBuffer();
			c.set("HANDICAP_", 9);
			c.concat(ht[i], (int)strlen(ht[i]));
			c.concat("_", 1);
			c.concat(tt[j], (int)strlen(tt[j]));
			NameKeyType k = TheNameKeyGenerator->nameToKey(c.str());
			bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
