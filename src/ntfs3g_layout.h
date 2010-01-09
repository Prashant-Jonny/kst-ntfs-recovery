/*
 * $Header$
 * 
 * That file is semi-modified layout.h from ntfs-3g library
 */

#ifndef NTFS3g_LAYOUT_INCLUDED
#define NTFS3g_LAYOUT_INCLUDED true

#ifndef const_cpu_to_le32
#define const_cpu_to_le64(x) (quint64(x))
#define const_cpu_to_le32(x) (quint32(x))
#define const_cpu_to_le16(x) (quint16(x))
#endif

typedef quint16     ntfschar;	/* for packed structures i can't to use QChar */

 /**
 * enum NTFS_RECORD_TYPES - cuted from ntfs-3g sources
 *
 * Magic identifiers present at the beginning of all ntfs record containing
 * records (like mft records for example).
 */

typedef enum NTFS_RECORD_TYPES
{
  /* Found in $MFT/$DATA. */
  magic_FILE = const_cpu_to_le32 (0x454c4946),	/* Mft entry. */
  magic_INDX = const_cpu_to_le32 (0x58444e49),	/* Index buffer. */
  magic_HOLE = const_cpu_to_le32 (0x454c4f48),	/* ? (NTFS 3.0+?) */

  /* Found in $LogFile/$DATA. */
  magic_RSTR = const_cpu_to_le32 (0x52545352),	/* Restart page. */
  magic_RCRD = const_cpu_to_le32 (0x44524352),	/* Log record page. */

  /* Found in $LogFile/$DATA.  (May be found in $MFT/$DATA, also?) */
  magic_CHKD = const_cpu_to_le32 (0x444b4843),	/* Modified by chkdsk. */

  /* Found in all ntfs record containing records. */
  magic_BAAD = const_cpu_to_le32 (0x44414142),	/* Failed multi sector
						   transfer was detected. */

  /*
   * Found in $LogFile/$DATA when a page is full or 0xff bytes and is
   * thus not initialized.  User has to initialize the page before using
   * it.
   */
  magic_empty = const_cpu_to_le32 (0xffffffff),	/* Record is empty and has
						   to be initialized before
						   it can be used. */
} NTFS_RECORD_TYPES;

/*
 * Generic magic comparison macros. Finally found a use for the ## preprocessor
 * operator! (-8
 */
#define ntfs_is_magic(x, m)	(   (quint32)(x) == (quint32)magic_##m )
#define ntfs_is_magicp(p, m)	( *(quint32*)(p) == (quint32)magic_##m )

/*
 * Specialised magic comparison macros for the NTFS_RECORD_TYPES defined above.
 */
#define ntfs_is_file_record(x)	( ntfs_is_magic (x, FILE) )
#define ntfs_is_file_recordp(p)	( ntfs_is_magicp(p, FILE) )
#define ntfs_is_mft_record(x)	( ntfs_is_file_record(x) )
#define ntfs_is_mft_recordp(p)	( ntfs_is_file_recordp(p) )
#define ntfs_is_indx_record(x)	( ntfs_is_magic (x, INDX) )
#define ntfs_is_indx_recordp(p)	( ntfs_is_magicp(p, INDX) )
#define ntfs_is_hole_record(x)	( ntfs_is_magic (x, HOLE) )
#define ntfs_is_hole_recordp(p)	( ntfs_is_magicp(p, HOLE) )

#define ntfs_is_rstr_record(x)	( ntfs_is_magic (x, RSTR) )
#define ntfs_is_rstr_recordp(p)	( ntfs_is_magicp(p, RSTR) )
#define ntfs_is_rcrd_record(x)	( ntfs_is_magic (x, RCRD) )
#define ntfs_is_rcrd_recordp(p)	( ntfs_is_magicp(p, RCRD) )

#define ntfs_is_chkd_record(x)	( ntfs_is_magic (x, CHKD) )
#define ntfs_is_chkd_recordp(p)	( ntfs_is_magicp(p, CHKD) )

#define ntfs_is_baad_record(x)	( ntfs_is_magic (x, BAAD) )
#define ntfs_is_baad_recordp(p)	( ntfs_is_magicp(p, BAAD) )

#define ntfs_is_empty_record(x)		( ntfs_is_magic (x, empty) )
#define ntfs_is_empty_recordp(p)	( ntfs_is_magicp(p, empty) )

/**
 * enum NTFS_SYSTEM_FILES - System files mft record numbers.
 *
 * All these files are always marked as used in the bitmap attribute of the
 * mft; presumably in order to avoid accidental allocation for random other
 * mft records. Also, the sequence number for each of the system files is
 * always equal to their mft record number and it is never modified.
 */
typedef enum NTFS_SYSTEM_FILES
{
  FILE_MFT = 0,			/* Master file table (mft). Data attribute
				   contains the entries and bitmap attribute
				   records which ones are in use (bit==1). */
  FILE_MFTMirr = 1,		/* Mft mirror: copy of first four mft records
				   in data attribute. If cluster size > 4kiB,
				   copy of first N mft records, with
				   N = cluster_size / mft_record_size. */
  FILE_LogFile = 2,		/* Journalling log in data attribute. */
  FILE_Volume = 3,		/* Volume name attribute and volume information
				   attribute (flags and ntfs version). Windows
				   refers to this file as volume DASD (Direct
				   Access Storage Device). */
  FILE_AttrDef = 4,		/* Array of attribute definitions in data
				   attribute. */
  FILE_root = 5,		/* Root directory. */
  FILE_Bitmap = 6,		/* Allocation bitmap of all clusters (lcns) in
				   data attribute. */
  FILE_Boot = 7,		/* Boot sector (always at cluster 0) in data
				   attribute. */
  FILE_BadClus = 8,		/* Contains all bad clusters in the non-resident
				   data attribute. */
  FILE_Secure = 9,		/* Shared security descriptors in data attribute
				   and two indexes into the descriptors.
				   Appeared in Windows 2000. Before that, this
				   file was named $Quota but was unused. */
  FILE_UpCase = 10,		/* Uppercase equivalents of all 65536 Unicode
				   characters in data attribute. */
  FILE_Extend = 11,		/* Directory containing other system files (eg.
				   $ObjId, $Quota, $Reparse and $UsnJrnl). This
				   is new to NTFS3.0. */
  FILE_reserved12 = 12,		/* Reserved for future use (records 12-15). */
  FILE_reserved13 = 13,
  FILE_reserved14 = 14,
  FILE_reserved15 = 15,
  FILE_first_user = 16,		/* First user file, used as test limit for
				   whether to allow opening a file or not. */
} NTFS_SYSTEM_FILES;

/**
 * enum MFT_RECORD_FLAGS -
 *
 * These are the so far known MFT_RECORD_* flags (16-bit) which contain
 * information about the mft record in which they are present.
 * 
 * MFT_RECORD_IS_4 exists on all $Extend sub-files.
 * It seems that it marks it is a metadata file with MFT record >24, however,
 * it is unknown if it is limited to metadata files only.
 *
 * MFT_RECORD_IS_VIEW_INDEX exists on every metafile with a non directory
 * index, that means an INDEX_ROOT and an INDEX_ALLOCATION with a name other
 * than "$I30". It is unknown if it is limited to metadata files only.
 */
typedef enum MFT_RECORD_FLAGS
{
  MFT_RECORD_IN_USE = const_cpu_to_le16 (0x0001),
  MFT_RECORD_IS_DIRECTORY = const_cpu_to_le16 (0x0002),
  MFT_RECORD_IS_4 = const_cpu_to_le16 (0x0004),
  MFT_RECORD_IS_VIEW_INDEX = const_cpu_to_le16 (0x0008),
  MFT_REC_SPACE_FILLER = 0xffff,	/* Just to make flags 16-bit. */
} __attribute__ ((__packed__)) MFT_RECORD_FLAGS;

/*
 * mft references (aka file references or file record segment references) are
 * used whenever a structure needs to refer to a record in the mft.
 *
 * A reference consists of a 48-bit index into the mft and a 16-bit sequence
 * number used to detect stale references.
 *
 * For error reporting purposes we treat the 48-bit index as a signed quantity.
 *
 * The sequence number is a circular counter (skipping 0) describing how many
 * times the referenced mft record has been (re)used. This has to match the
 * sequence number of the mft record being referenced, otherwise the reference
 * is considered stale and removed (FIXME: only ntfsck or the driver itself?).
 *
 * If the sequence number is zero it is assumed that no sequence number
 * consistency checking should be performed.
 *
 * FIXME: Since inodes are 32-bit as of now, the driver needs to always check
 * for high_part being 0 and if not either BUG(), cause a panic() or handle
 * the situation in some other way. This shouldn't be a problem as a volume has
 * to become HUGE in order to need more than 32-bits worth of mft records.
 * Assuming the standard mft record size of 1kb only the records (never mind
 * the non-resident attributes, etc.) would require 4Tb of space on their own
 * for the first 32 bits worth of records. This is only if some strange person
 * doesn't decide to foul play and make the mft sparse which would be a really
 * horrible thing to do as it would trash our current driver implementation. )-:
 * Do I hear screams "we want 64-bit inodes!" ?!? (-;
 *
 * FIXME: The mft zone is defined as the first 12% of the volume. This space is
 * reserved so that the mft can grow contiguously and hence doesn't become
 * fragmented. Volume free space includes the empty part of the mft zone and
 * when the volume's free 88% are used up, the mft zone is shrunk by a factor
 * of 2, thus making more space available for more files/data. This process is
 * repeated every time there is no more free space except for the mft zone until
 * there really is no more free space.
 */

/*
 * Typedef the MFT_REF as a 64-bit value for easier handling.
 * Also define two unpacking macros to get to the reference (MREF) and
 * sequence number (MSEQNO) respectively.
 * The _LE versions are to be applied on little endian MFT_REFs.
 * Note: The _LE versions will return a CPU endian formatted value!
 */
#define MFT_REF_MASK_CPU 0x0000ffffffffffffULL
#define MFT_REF_MASK_LE const_cpu_to_le64(MFT_REF_MASK_CPU)

typedef quint64     MFT_REF;

#define MK_MREF(m, s)	((MFT_REF)(((MFT_REF)(s) << 48) |		\
					((MFT_REF)(m) & MFT_REF_MASK_CPU)))
#define MK_LE_MREF(m, s) const_cpu_to_le64(((MFT_REF)(((MFT_REF)(s) << 48) | \
					((MFT_REF)(m) & MFT_REF_MASK_CPU))))

#define MREF(x)		((quint64)((x) & MFT_REF_MASK_CPU))
#define MSEQNO(x)	((quint16)(((x) >> 48) & 0xffff))
#define MREF_LE(x)	((quint64)(const_le64_to_cpu(x) & MFT_REF_MASK_CPU))
#define MSEQNO_LE(x)	((quint16)((const_le64_to_cpu(x) >> 48) & 0xffff))

#define IS_ERR_MREF(x)	(((x) & 0x0000800000000000ULL) ? 1 : 0)
#define ERR_MREF(x)	((quint64)((qint64)(x)))
#define MREF_ERR(x)	((qint16)((qint64)(x)))

/**
 * struct MFT_RECORD - An MFT record layout (NTFS 3.1+)
 *
 * The mft record header present at the beginning of every record in the mft.
 * This is followed by a sequence of variable length attribute records which
 * is terminated by an attribute of type AT_END which is a truncated attribute
 * in that it only consists of the attribute type code AT_END and none of the
 * other members of the attribute structure are present.
 */
typedef struct MFT_RECORD
{
/*Ofs*/
/*  0	NTFS_RECORD; -- Unfolded here as gcc doesn't like unnamed structs. */
  NTFS_RECORD_TYPES   magic;	/* Usually the magic is "FILE". */
  quint16             usa_ofs;	/* See NTFS_RECORD definition above. */
  quint16             usa_count;	/* See NTFS_RECORD definition above. */

  /*  8 */ qint64     lsn;
  /* $LogFile sequence number for this record.
     Changed every time the record is modified. */
  /* 16 */ quint16    sequence_number;
  /* Number of times this mft record has been
     reused. (See description for MFT_REF
     above.) NOTE: The increment (skipping zero)
     is done when the file is deleted. NOTE: If
     this is zero it is left zero. */
  /* 18 */ quint16    link_count;
  /* Number of hard links, i.e. the number of
     directory entries referencing this record.
     NOTE: Only used in mft base records.
     NOTE: When deleting a directory entry we
     check the link_count and if it is 1 we
     delete the file. Otherwise we delete the
     FILE_NAME_ATTR being referenced by the
     directory entry from the mft record and
     decrement the link_count.
     FIXME: Careful with Win32 + DOS names! */
  /* 20 */ quint16    attrs_offset;
  /* Byte offset to the first attribute in this
     mft record from the start of the mft record.
     NOTE: Must be aligned to 8-byte boundary. */
  /* 22 */ MFT_RECORD_FLAGS flags;
  /* Bit array of MFT_RECORD_FLAGS. When a file
     is deleted, the MFT_RECORD_IN_USE flag is
     set to zero. */
  /* 24 */ quint32    bytes_in_use;
  /* Number of bytes used in this mft record.
     NOTE: Must be aligned to 8-byte boundary. */
  /* 28 */ quint32    bytes_allocated;
  /* Number of bytes allocated for this mft
     record. This should be equal to the mft
     record size. */
  /* 32 */ MFT_REF    base_mft_record;
  /* This is zero for base mft records.
     When it is not zero it is a mft reference
     pointing to the base mft record to which
     this record belongs (this is then used to
     locate the attribute list attribute present
     in the base record which describes this
     extension record and hence might need
     modification when the extension record
     itself is modified, also locating the
     attribute list also means finding the other
     potential extents, belonging to the non-base
     mft record). */
  /* 40 */ quint16    next_attr_instance;
  /* The instance number that will be
     assigned to the next attribute added to this
     mft record. NOTE: Incremented each time
     after it is used. NOTE: Every time the mft
     record is reused this number is set to zero.
     NOTE: The first instance number is always 0.
   */
/* The below fields are specific to NTFS 3.1+ (Windows XP and above): */
  /* 42 */ quint16    reserved;
  /* Reserved/alignment. */
  /* 44 */ quint32    mft_record_number;
  /* Number of this mft record. */
/* sizeof() = 48 bytes */
/*
 * When (re)using the mft record, we place the update sequence array at this
 * offset, i.e. before we start with the attributes. This also makes sense,
 * otherwise we could run into problems with the update sequence array
 * containing in itself the last two bytes of a sector which would mean that
 * multi sector transfer protection wouldn't work. As you can't protect data
 * by overwriting it since you then can't get it back...
 * When reading we obviously use the data from the ntfs record header.
 */
} __attribute__ ((__packed__)) MFT_RECORD;

/**
 * enum ATTR_TYPES - System defined attributes (32-bit).
 *
 * Each attribute type has a corresponding attribute name (Unicode string of
 * maximum 64 character length) as described by the attribute definitions
 * present in the data attribute of the $AttrDef system file.
 * 
 * On NTFS 3.0 volumes the names are just as the types are named in the below
 * enum exchanging AT_ for the dollar sign ($). If that isn't a revealing
 * choice of symbol... (-;
 */
typedef enum ATTR_TYPES
{
  AT_UNUSED = const_cpu_to_le32 (0),
  AT_STANDARD_INFORMATION = const_cpu_to_le32 (0x10),
  AT_ATTRIBUTE_LIST = const_cpu_to_le32 (0x20),
  AT_FILE_NAME = const_cpu_to_le32 (0x30),
  AT_OBJECT_ID = const_cpu_to_le32 (0x40),
  AT_SECURITY_DESCRIPTOR = const_cpu_to_le32 (0x50),
  AT_VOLUME_NAME = const_cpu_to_le32 (0x60),
  AT_VOLUME_INFORMATION = const_cpu_to_le32 (0x70),
  AT_DATA = const_cpu_to_le32 (0x80),
  AT_INDEX_ROOT = const_cpu_to_le32 (0x90),
  AT_INDEX_ALLOCATION = const_cpu_to_le32 (0xa0),
  AT_BITMAP = const_cpu_to_le32 (0xb0),
  AT_REPARSE_POINT = const_cpu_to_le32 (0xc0),
  AT_EA_INFORMATION = const_cpu_to_le32 (0xd0),
  AT_EA = const_cpu_to_le32 (0xe0),
  AT_PROPERTY_SET = const_cpu_to_le32 (0xf0),
  AT_LOGGED_UTILITY_STREAM = const_cpu_to_le32 (0x100),
  AT_FIRST_USER_DEFINED_ATTRIBUTE = const_cpu_to_le32 (0x1000),
  AT_END = const_cpu_to_le32 (0xffffffff),
} ATTR_TYPES;

/**
 * enum ATTR_DEF_FLAGS -
 *
 * The flags (32-bit) describing attribute properties in the attribute
 * definition structure.  FIXME: This information is based on Regis's
 * information and, according to him, it is not certain and probably
 * incomplete.  The INDEXABLE flag is fairly certainly correct as only the file
 * name attribute has this flag set and this is the only attribute indexed in
 * NT4.
 */
typedef enum ATTR_DEF_FLAGS
{
  ATTR_DEF_INDEXABLE = const_cpu_to_le32 (0x02),	/* Attribute can be
							   indexed. */
  ATTR_DEF_MULTIPLE = const_cpu_to_le32 (0x04),	/* Attribute type
						   can be present multiple times in the
						   mft records of an inode. */
  ATTR_DEF_NOT_ZERO = const_cpu_to_le32 (0x08),	/* Attribute value
						   must contain at least one non-zero
						   byte. */
  ATTR_DEF_INDEXED_UNIQUE = const_cpu_to_le32 (0x10),	/* Attribute must be
							   indexed and the attribute value must be
							   unique for the attribute type in all of
							   the mft records of an inode. */
  ATTR_DEF_NAMED_UNIQUE = const_cpu_to_le32 (0x20),	/* Attribute must be
							   named and the name must be unique for
							   the attribute type in all of the mft
							   records of an inode. */
  ATTR_DEF_RESIDENT = const_cpu_to_le32 (0x40),	/* Attribute must be
						   resident. */
  ATTR_DEF_ALWAYS_LOG = const_cpu_to_le32 (0x80),	/* Always log
							   modifications to this attribute,
							   regardless of whether it is resident or
							   non-resident.  Without this, only log
							   modifications if the attribute is
							   resident. */
} ATTR_DEF_FLAGS;

/**
 * enum COLLATION_RULES - The collation rules for sorting views/indexes/etc
 * (32-bit).
 *
 * COLLATION_UNICODE_STRING - Collate Unicode strings by comparing their binary
 *	Unicode values, except that when a character can be uppercased, the
 *	upper case value collates before the lower case one.
 * COLLATION_FILE_NAME - Collate file names as Unicode strings. The collation
 *	is done very much like COLLATION_UNICODE_STRING. In fact I have no idea
 *	what the difference is. Perhaps the difference is that file names
 *	would treat some special characters in an odd way (see
 *	unistr.c::ntfs_collate_names() and unistr.c::legal_ansi_char_array[]
 *	for what I mean but COLLATION_UNICODE_STRING would not give any special
 *	treatment to any characters at all, but this is speculation.
 * COLLATION_NTOFS_ULONG - Sorting is done according to ascending u32 key
 *	values. E.g. used for $SII index in FILE_Secure, which sorts by
 *	security_id (u32).
 * COLLATION_NTOFS_SID - Sorting is done according to ascending SID values.
 *	E.g. used for $O index in FILE_Extend/$Quota.
 * COLLATION_NTOFS_SECURITY_HASH - Sorting is done first by ascending hash
 *	values and second by ascending security_id values. E.g. used for $SDH
 *	index in FILE_Secure.
 * COLLATION_NTOFS_ULONGS - Sorting is done according to a sequence of ascending
 *	u32 key values. E.g. used for $O index in FILE_Extend/$ObjId, which
 *	sorts by object_id (16-byte), by splitting up the object_id in four
 *	u32 values and using them as individual keys. E.g. take the following
 *	two security_ids, stored as follows on disk:
 *		1st: a1 61 65 b7 65 7b d4 11 9e 3d 00 e0 81 10 42 59
 *		2nd: 38 14 37 d2 d2 f3 d4 11 a5 21 c8 6b 79 b1 97 45
 *	To compare them, they are split into four u32 values each, like so:
 *		1st: 0xb76561a1 0x11d47b65 0xe0003d9e 0x59421081
 *		2nd: 0xd2371438 0x11d4f3d2 0x6bc821a5 0x4597b179
 *	Now, it is apparent why the 2nd object_id collates after the 1st: the
 *	first u32 value of the 1st object_id is less than the first u32 of
 *	the 2nd object_id. If the first u32 values of both object_ids were
 *	equal then the second u32 values would be compared, etc.
 */
typedef enum COLLATION_RULES
{
  COLLATION_BINARY = const_cpu_to_le32 (0),	/* Collate by binary
						   compare where the first byte is most
						   significant. */
  COLLATION_FILE_NAME = const_cpu_to_le32 (1),	/* Collate file names
						   as Unicode strings. */
  COLLATION_UNICODE_STRING = const_cpu_to_le32 (2),	/* Collate Unicode
							   strings by comparing their binary
							   Unicode values, except that when a
							   character can be uppercased, the upper
							   case value collates before the lower
							   case one. */
  COLLATION_NTOFS_ULONG = const_cpu_to_le32 (16),
  COLLATION_NTOFS_SID = const_cpu_to_le32 (17),
  COLLATION_NTOFS_SECURITY_HASH = const_cpu_to_le32 (18),
  COLLATION_NTOFS_ULONGS = const_cpu_to_le32 (19),
} COLLATION_RULES;

/**
 * struct ATTR_DEF -
 *
 * The data attribute of FILE_AttrDef contains a sequence of attribute
 * definitions for the NTFS volume. With this, it is supposed to be safe for an
 * older NTFS driver to mount a volume containing a newer NTFS version without
 * damaging it (that's the theory. In practice it's: not damaging it too much).
 * Entries are sorted by attribute type. The flags describe whether the
 * attribute can be resident/non-resident and possibly other things, but the
 * actual bits are unknown.
 */
typedef struct ATTR_DEF
{
/*hex ofs*/
  /*  0 */ quint16    name[0x40];
  /* Unicode name of the attribute. Zero terminated. */
  /* 80 */ ATTR_TYPES type;
  /* Type of the attribute. */
  /* 84 */ quint32    display_rule;
  /* Default display rule.
     FIXME: What does it mean? (AIA) */
  /* 88 */ COLLATION_RULES collation_rule;
  /* Default collation rule. */
  /* 8c */ ATTR_DEF_FLAGS flags;
  /* Flags describing the attribute. */
  /* 90 */ qint64     min_size;
  /* Optional minimum attribute size. */
  /* 98 */ qint64     max_size;
  /* Maximum size of attribute. */
/* sizeof() = 0xa0 or 160 bytes */
} __attribute__ ((__packed__)) ATTR_DEF;

/**
 * enum ATTR_FLAGS - Attribute flags (16-bit).
 */
typedef enum ATTR_FLAGS
{
  ATTR_IS_COMPRESSED = const_cpu_to_le16 (0x0001),
  ATTR_COMPRESSION_MASK = const_cpu_to_le16 (0x00ff),	/* Compression
							   method mask. Also, first
							   illegal value. */
  ATTR_IS_ENCRYPTED = const_cpu_to_le16 (0x4000),
  ATTR_IS_SPARSE = const_cpu_to_le16 (0x8000),
} __attribute__ ((__packed__)) ATTR_FLAGS;

/*
 * Attribute compression.
 *
 * Only the data attribute is ever compressed in the current ntfs driver in
 * Windows. Further, compression is only applied when the data attribute is
 * non-resident. Finally, to use compression, the maximum allowed cluster size
 * on a volume is 4kib.
 *
 * The compression method is based on independently compressing blocks of X
 * clusters, where X is determined from the compression_unit value found in the
 * non-resident attribute record header (more precisely: X = 2^compression_unit
 * clusters). On Windows NT/2k, X always is 16 clusters (compression_unit = 4).
 *
 * There are three different cases of how a compression block of X clusters
 * can be stored:
 *
 *   1) The data in the block is all zero (a sparse block):
 *	  This is stored as a sparse block in the runlist, i.e. the runlist
 *	  entry has length = X and lcn = -1. The mapping pairs array actually
 *	  uses a delta_lcn value length of 0, i.e. delta_lcn is not present at
 *	  all, which is then interpreted by the driver as lcn = -1.
 *	  NOTE: Even uncompressed files can be sparse on NTFS 3.0 volumes, then
 *	  the same principles apply as above, except that the length is not
 *	  restricted to being any particular value.
 *
 *   2) The data in the block is not compressed:
 *	  This happens when compression doesn't reduce the size of the block
 *	  in clusters. I.e. if compression has a small effect so that the
 *	  compressed data still occupies X clusters, then the uncompressed data
 *	  is stored in the block.
 *	  This case is recognised by the fact that the runlist entry has
 *	  length = X and lcn >= 0. The mapping pairs array stores this as
 *	  normal with a run length of X and some specific delta_lcn, i.e.
 *	  delta_lcn has to be present.
 *
 *   3) The data in the block is compressed:
 *	  The common case. This case is recognised by the fact that the run
 *	  list entry has length L < X and lcn >= 0. The mapping pairs array
 *	  stores this as normal with a run length of X and some specific
 *	  delta_lcn, i.e. delta_lcn has to be present. This runlist entry is
 *	  immediately followed by a sparse entry with length = X - L and
 *	  lcn = -1. The latter entry is to make up the vcn counting to the
 *	  full compression block size X.
 *
 * In fact, life is more complicated because adjacent entries of the same type
 * can be coalesced. This means that one has to keep track of the number of
 * clusters handled and work on a basis of X clusters at a time being one
 * block. An example: if length L > X this means that this particular runlist
 * entry contains a block of length X and part of one or more blocks of length
 * L - X. Another example: if length L < X, this does not necessarily mean that
 * the block is compressed as it might be that the lcn changes inside the block
 * and hence the following runlist entry describes the continuation of the
 * potentially compressed block. The block would be compressed if the
 * following runlist entry describes at least X - L sparse clusters, thus
 * making up the compression block length as described in point 3 above. (Of
 * course, there can be several runlist entries with small lengths so that the
 * sparse entry does not follow the first data containing entry with
 * length < X.)
 *
 * NOTE: At the end of the compressed attribute value, there most likely is not
 * just the right amount of data to make up a compression block, thus this data
 * is not even attempted to be compressed. It is just stored as is, unless
 * the number of clusters it occupies is reduced when compressed in which case
 * it is stored as a compressed compression block, complete with sparse
 * clusters at the end.
 */

/**
 * enum RESIDENT_ATTR_FLAGS - Flags of resident attributes (8-bit).
 */
typedef enum RESIDENT_ATTR_FLAGS
{
  RESIDENT_ATTR_IS_INDEXED = 0x01,	/* Attribute is referenced in an index
					   (has implications for deleting and
					   modifying the attribute). */
} __attribute__ ((__packed__)) RESIDENT_ATTR_FLAGS;

/**
 * struct ATTR_RECORD - Attribute record header.
 *
 * Always aligned to 8-byte boundary.
 */
typedef qint64      VCN;	/* virtual cluster number :
				   anoter words = offset in linear data */
typedef qint64      LCN;	/* logical cluster number :
				   another words = real cluster number */

typedef struct ATTR_REC
{
/*Ofs*/
  /*  0 */ ATTR_TYPES type;
  /* The (32-bit) type of the attribute. */
  /*  4 */ quint32    length;
  /* Byte size of the resident part of the
     attribute (aligned to 8-byte boundary).
     Used to get to the next attribute. */
  /*  8 */ quint8     non_resident;
  /* If 0, attribute is resident.
     If 1, attribute is non-resident. */
  /*  9 */ quint8     name_length;
  /* Unicode character size of name of attribute.
     0 if unnamed. */
  /* 10 */ quint16    name_offset;
  /* If name_length != 0, the byte offset to the
     beginning of the name from the attribute
     record. Note that the name is stored as a
     Unicode string. When creating, place offset
     just at the end of the record header. Then,
     follow with attribute value or mapping pairs
     array, resident and non-resident attributes
     respectively, aligning to an 8-byte
     boundary. */
  /* 12 */ ATTR_FLAGS flags;
  /* Flags describing the attribute. */
  /* 14 */ quint16    instance;
  /* The instance of this attribute record. This
     number is unique within this mft record (see
     MFT_RECORD/next_attribute_instance notes
     above for more details). */
/* 16*/ union
  {
    /* Resident attributes. */
    struct
    {
      /* 16 */ quint32    value_length;
      /* Byte size of attribute value. */
      /* 20 */ quint16    value_offset;
      /* Byte offset of the attribute
         value from the start of the
         attribute record. When creating,
         align to 8-byte boundary if we
         have a name present as this might
         not have a length of a multiple
         of 8-bytes. */
      /* 22 */ RESIDENT_ATTR_FLAGS resident_flags;
      /* See above. */
      /* 23 */ qint8      reservedR;
      /* Reserved/alignment to 8-byte boundary. */
      /* 24 */ void      *resident_end[0];
      /* Use offsetof(ATTR_RECORD, resident_end) to get size of a resident attribute. */
    } __attribute__ ((__packed__));
    /* Non-resident attributes. */
    struct
    {
      /* 16 */ VCN        lowest_vcn;
      /* Lowest valid virtual cluster number
         for this portion of the attribute value or
         0 if this is the only extent (usually the
         case). - Only when an attribute list is used
         does lowest_vcn != 0 ever occur. */
      /* 24 */ VCN        highest_vcn;
      /* Highest valid vcn of this extent of
         the attribute value. - Usually there is only one
         portion, so this usually equals the attribute
         value size in clusters minus 1. Can be -1 for
         zero length files. Can be 0 for "single extent"
         attributes. */
      /* 32 */ quint16    mapping_pairs_offset;
      /* Byte offset from the
         beginning of the structure to the mapping pairs
         array which contains the mappings between the
         vcns and the logical cluster numbers (lcns).
         When creating, place this at the end of this
         record header aligned to 8-byte boundary. */
      /* 34 */ quint8     compression_unit;
      /* The compression unit expressed
         as the log to the base 2 of the number of
         clusters in a compression unit. 0 means not
         compressed. (This effectively limits the
         compression unit size to be a power of two
         clusters.) WinNT4 only uses a value of 4. */
      /* 35 */ quint8     reserved1[5];
      /* Align to 8-byte boundary. */
/* The sizes below are only used when lowest_vcn is zero, as otherwise it would
   be difficult to keep them up-to-date.*/
      /* 40 */ qint64     allocated_size;
      /* Byte size of disk space
         allocated to hold the attribute value. Always
         is a multiple of the cluster size. When a file
         is compressed, this field is a multiple of the
         compression block size (2^compression_unit) and
         it represents the logically allocated space
         rather than the actual on disk usage. For this
         use the compressed_size (see below). */
      /* 48 */ qint64     data_size;
      /* Byte size of the attribute
         value. Can be larger than allocated_size if
         attribute value is compressed or sparse. */
      /* 56 */ qint64     initialized_size;
      /* Byte size of initialized
         portion of the attribute value. Usually equals
         data_size. */
      /* 64 */ void      *non_resident_end[0];
      /* Use offsetof(ATTR_RECORD,
         non_resident_end) to get
         size of a non resident
         attribute. */
/* sizeof(uncompressed attr) = 64*/
      /* 64 */ qint64     compressed_size;
      /* Byte size of the attribute
         value after compression. Only present when
         compressed. Always is a multiple of the
         cluster size. Represents the actual amount of
         disk space being used on the disk. */
/* 72 */ void      *compressed_end[0];
      /* Use offsetof(ATTR_RECORD, compressed_end) to
         get size of a compressed attribute. */
/* sizeof(compressed attr) = 72*/
    } __attribute__ ((__packed__));
  } __attribute__ ((__packed__));
} __attribute__ ((__packed__)) ATTR_RECORD;

typedef ATTR_RECORD ATTR_REC;

/**
 * enum FILE_ATTR_FLAGS - File attribute flags (32-bit).
 */
typedef enum FILE_ATTR_FLAGS
{
  /*
   * These flags are only present in the STANDARD_INFORMATION attribute
   * (in the field file_attributes).
   */
  FILE_ATTR_READONLY = const_cpu_to_le32 (0x00000001),
  FILE_ATTR_HIDDEN = const_cpu_to_le32 (0x00000002),
  FILE_ATTR_SYSTEM = const_cpu_to_le32 (0x00000004),
  /* Old DOS volid. Unused in NT. = cpu_to_le32(0x00000008), */

  FILE_ATTR_DIRECTORY = const_cpu_to_le32 (0x00000010),
  /* FILE_ATTR_DIRECTORY is not considered valid in NT. It is reserved
     for the DOS SUBDIRECTORY flag. */
  FILE_ATTR_ARCHIVE = const_cpu_to_le32 (0x00000020),
  FILE_ATTR_DEVICE = const_cpu_to_le32 (0x00000040),
  FILE_ATTR_NORMAL = const_cpu_to_le32 (0x00000080),

  FILE_ATTR_TEMPORARY = const_cpu_to_le32 (0x00000100),
  FILE_ATTR_SPARSE_FILE = const_cpu_to_le32 (0x00000200),
  FILE_ATTR_REPARSE_POINT = const_cpu_to_le32 (0x00000400),
  FILE_ATTR_COMPRESSED = const_cpu_to_le32 (0x00000800),

  FILE_ATTR_OFFLINE = const_cpu_to_le32 (0x00001000),
  FILE_ATTR_NOT_CONTENT_INDEXED = const_cpu_to_le32 (0x00002000),
  FILE_ATTR_ENCRYPTED = const_cpu_to_le32 (0x00004000),

  FILE_ATTR_VALID_FLAGS = const_cpu_to_le32 (0x00007fb7),
  /* FILE_ATTR_VALID_FLAGS masks out the old DOS VolId and the
     FILE_ATTR_DEVICE and preserves everything else. This mask
     is used to obtain all flags that are valid for reading. */
  FILE_ATTR_VALID_SET_FLAGS = const_cpu_to_le32 (0x000031a7),
  /* FILE_ATTR_VALID_SET_FLAGS masks out the old DOS VolId, the
     FILE_ATTR_DEVICE, FILE_ATTR_DIRECTORY, FILE_ATTR_SPARSE_FILE,
     FILE_ATTR_REPARSE_POINT, FILE_ATRE_COMPRESSED and FILE_ATTR_ENCRYPTED
     and preserves the rest. This mask is used to to obtain all flags that
     are valid for setting. */

	/**
	 * FILE_ATTR_I30_INDEX_PRESENT - Is it a directory?
	 *
	 * This is a copy of the MFT_RECORD_IS_DIRECTORY bit from the mft
	 * record, telling us whether this is a directory or not, i.e. whether
	 * it has an index root attribute named "$I30" or not.
	 * 
	 * This flag is only present in the FILE_NAME attribute (in the 
	 * file_attributes field).
	 */
  FILE_ATTR_I30_INDEX_PRESENT = const_cpu_to_le32 (0x10000000),

	/**
	 * FILE_ATTR_VIEW_INDEX_PRESENT - Does have a non-directory index?
	 * 
	 * This is a copy of the MFT_RECORD_IS_VIEW_INDEX bit from the mft
	 * record, telling us whether this file has a view index present (eg.
	 * object id index, quota index, one of the security indexes and the
	 * reparse points index).
	 *
	 * This flag is only present in the $STANDARD_INFORMATION and
	 * $FILE_NAME attributes.
	 */
  FILE_ATTR_VIEW_INDEX_PRESENT = const_cpu_to_le32 (0x20000000),
} __attribute__ ((__packed__)) FILE_ATTR_FLAGS;

/*
 * NOTE on times in NTFS: All times are in MS standard time format, i.e. they
 * are the number of 100-nanosecond intervals since 1st January 1601, 00:00:00
 * universal coordinated time (UTC). (In Linux time starts 1st January 1970,
 * 00:00:00 UTC and is stored as the number of 1-second intervals since then.)
 */

/**
 * struct STANDARD_INFORMATION - Attribute: Standard information (0x10).
 *
 * NOTE: Always resident.
 * NOTE: Present in all base file records on a volume.
 * NOTE: There is conflicting information about the meaning of each of the time
 *	 fields but the meaning as defined below has been verified to be
 *	 correct by practical experimentation on Windows NT4 SP6a and is hence
 *	 assumed to be the one and only correct interpretation.
 */
typedef struct STANDARD_INFORMATION
{
/*Ofs*/
  /*  0 */ qint64     creation_time;
  /* Time file was created. Updated when  a filename is changed(?). */
  /*  8 */ qint64     last_data_change_time;
  /* Time the data attribute was last modified. */
  /* 16 */ qint64     last_mft_change_time;
  /* Time this mft record was last modified. */
  /* 24 */ qint64     last_access_time;
  /* Approximate time when the file was 
     Slast accessed (obviously this is not
     updated on read-only volumes). In
     Windows this is only updated when
     accessed if some time delta has
     passed since the last update. Also,
     last access times updates can be
     disabled altogether for speed. */
  /* 32 */ FILE_ATTR_FLAGS file_attributes;
  /* Flags describing the file. */
/* 36*/ union
  {
    /* NTFS 1.2 (and previous, presumably) */
    struct
    {
      /* 36 */ quint8     reserved12[12];
      /* Reserved/alignment to 8-byte boundary. */
      /* 48 */ void      *v1_end[0];
      /* Marker for offsetof(). */
    } __attribute__ ((__packed__));
/* sizeof() = 48 bytes */
    /* NTFS 3.0 */
    struct
    {
/*
 * If a volume has been upgraded from a previous NTFS version, then these
 * fields are present only if the file has been accessed since the upgrade.
 * Recognize the difference by comparing the length of the resident attribute
 * value. If it is 48, then the following fields are missing. If it is 72 then
 * the fields are present. Maybe just check like this:
 *	if (resident.ValueLength < sizeof(STANDARD_INFORMATION)) {
 *		Assume NTFS 1.2- format.
 *		If (volume version is 3.0+)
 *			Upgrade attribute to NTFS 3.0 format.
 *		else
 *			Use NTFS 1.2- format for access.
 *	} else
 *		Use NTFS 3.0 format for access.
 * Only problem is that it might be legal to set the length of the value to
 * arbitrarily large values thus spoiling this check. - But chkdsk probably
 * views that as a corruption, assuming that it behaves like this for all
 * attributes.
 */
      /* 36 */ quint32    maximum_versions;
      /* Maximum allowed versions for file. Zero if version numbering is disabled. */
      /* 40 */ quint32    version_number;
      /* This file's version (if any). Set to zero if maximum_versions is zero. */
      /* 44 */ quint32    class_id;
      /* Class id from bidirectional class id index (?). */
      /* 48 */ quint32    owner_id;
      /* Owner_id of the user owning the file. Translate via $Q index in FILE_Extend
         /$Quota to the quota control entry for the user owning the file. Zero if quotas are disabled. */
      /* 52 */ quint32    security_id;
      /* Security_id for the file.  Translate via $SII index and $SDS data stream in FILE_Secure to the security descriptor. */
      /* 56 */ quint64    quota_charged;
      /* Byte size of the charge to the quota for all streams of the file. Note: Is zero if quotas are disabled. */
      /* 64 */ quint64    usn;
      /* Last update sequence number
         of the file. This is a direct index into the
         change (aka usn) journal file. It is zero if
         the usn journal is disabled.
         NOTE: To disable the journal need to delete
         the journal file itself and to then walk the
         whole mft and set all Usn entries in all mft
         records to zero! (This can take a while!)
         The journal is FILE_Extend/$UsnJrnl. Win2k
         will recreate the journal and initiate
         logging if necessary when mounting the
         partition. This, in contrast to disabling the
         journal is a very fast process, so the user
         won't even notice it. */
      /* 72 */ void      *v3_end[0];
      /* Marker for offsetof(). */
    } __attribute__ ((__packed__));
  } __attribute__ ((__packed__));
/* sizeof() = 72 bytes (NTFS 3.0) */
} __attribute__ ((__packed__)) STANDARD_INFORMATION;

/**
 * struct ATTR_LIST_ENTRY - Attribute: Attribute list (0x20).
 *
 * - Can be either resident or non-resident.
 * - Value consists of a sequence of variable length, 8-byte aligned,
 * ATTR_LIST_ENTRY records.
 * - The attribute list attribute contains one entry for each attribute of
 * the file in which the list is located, except for the list attribute
 * itself. The list is sorted: first by attribute type, second by attribute
 * name (if present), third by instance number. The extents of one
 * non-resident attribute (if present) immediately follow after the initial
 * extent. They are ordered by lowest_vcn and have their instance set to zero.
 * It is not allowed to have two attributes with all sorting keys equal.
 * - Further restrictions:
 *	- If not resident, the vcn to lcn mapping array has to fit inside the
 *	  base mft record.
 *	- The attribute list attribute value has a maximum size of 256kb. This
 *	  is imposed by the Windows cache manager.
 * - Attribute lists are only used when the attributes of mft record do not
 * fit inside the mft record despite all attributes (that can be made
 * non-resident) having been made non-resident. This can happen e.g. when:
 *	- File has a large number of hard links (lots of file name
 *	  attributes present).
 *	- The mapping pairs array of some non-resident attribute becomes so
 *	  large due to fragmentation that it overflows the mft record.
 *	- The security descriptor is very complex (not applicable to
 *	  NTFS 3.0 volumes).
 *	- There are many named streams.
 */
typedef struct ATTR_LIST_ENTRY
{
/*Ofs*/
  /*  0 */ ATTR_TYPES type;
  /* Type of referenced attribute. */
  /*  4 */ quint16    length;
  /* Byte size of this entry. */
  /*  6 */ quint8     name_length;
  /* Size in Unicode chars of the name of the
     attribute or 0 if unnamed. */
  /*  7 */ quint8     name_offset;
  /* Byte offset to beginning of attribute name
     (always set this to where the name would
     start even if unnamed). */
  /*  8 */ VCN        lowest_vcn;
  /* Lowest virtual cluster number of this portion
     of the attribute value. This is usually 0. It
     is non-zero for the case where one attribute
     does not fit into one mft record and thus
     several mft records are allocated to hold
     this attribute. In the latter case, each mft
     record holds one extent of the attribute and
     there is one attribute list entry for each
     extent. NOTE: This is DEFINITELY a signed
     value! The windows driver uses cmp, followed
     by jg when comparing this, thus it treats it
     as signed. */
  /* 16 */ MFT_REF    mft_reference;
  /* The reference of the mft record holding
     the ATTR_RECORD for this portion of the
     attribute value. */
  /* 24 */ quint16    instance;
  /* If lowest_vcn = 0, the instance of the
     attribute being referenced; otherwise 0. */
  /* 26 */ ntfschar   name[0];
  /* Use when creating only. When reading use
     name_offset to determine the location of the
     name. */
/* sizeof() = 26 + (attribute_name_length * 2) bytes */
} __attribute__ ((__packed__)) ATTR_LIST_ENTRY;

#define NTFS_MAX_NAME_LEN	255

/**
 * enum FILE_NAME_TYPE_FLAGS - Possible namespaces for filenames in ntfs.
 * (8-bit).
 */
typedef enum FILE_NAME_TYPE_FLAGS
{
  FILE_NAME_POSIX = 0x00,
  /* This is the largest namespace. It is case sensitive and
     allows all Unicode characters except for: '\0' and '/'.
     Beware that in WinNT/2k files which eg have the same name
     except for their case will not be distinguished by the
     standard utilities and thus a "del filename" will delete
     both "filename" and "fileName" without warning. */
  FILE_NAME_WIN32 = 0x01,
  /* The standard WinNT/2k NTFS long filenames. Case insensitive.
     All Unicode chars except: '\0', '"', '*', '/', ':', '<',
     '>', '?', '\' and '|'. Further, names cannot end with a '.'
     or a space. */
  FILE_NAME_DOS = 0x02,
  /* The standard DOS filenames (8.3 format). Uppercase only.
     All 8-bit characters greater space, except: '"', '*', '+',
     ',', '/', ':', ';', '<', '=', '>', '?' and '\'. */
  FILE_NAME_WIN32_AND_DOS = 0x03,
  /* 3 means that both the Win32 and the DOS filenames are
     identical and hence have been saved in this single filename
     record. */
} __attribute__ ((__packed__)) FILE_NAME_TYPE_FLAGS;

/**
 * struct FILE_NAME_ATTR - Attribute: Filename (0x30).
 *
 * NOTE: Always resident.
 * NOTE: All fields, except the parent_directory, are only updated when the
 *	 filename is changed. Until then, they just become out of sync with
 *	 reality and the more up to date values are present in the standard
 *	 information attribute.
 * NOTE: There is conflicting information about the meaning of each of the time
 *	 fields but the meaning as defined below has been verified to be
 *	 correct by practical experimentation on Windows NT4 SP6a and is hence
 *	 assumed to be the one and only correct interpretation.
 */
typedef struct FILE_NAME_ATTR
{
/*hex ofs*/
  /*  0 */ MFT_REF    parent_directory;
  /* Directory this filename is
     referenced from. */
  /*  8 */ qint64     creation_time;
  /* Time file was created. */
  /* 10 */ qint64     last_data_change_time;
  /* Time the data attribute was last
     modified. */
  /* 18 */ qint64     last_mft_change_time;
  /* Time this mft record was last
     modified. */
  /* 20 */ qint64     last_access_time;
  /* Last time this mft record was
     accessed. */
  /* 28 */ qint64     allocated_size;
  /* Byte size of on-disk allocated space
     for the data attribute.  So for
     normal $DATA, this is the
     allocated_size from the unnamed
     $DATA attribute and for compressed
     and/or sparse $DATA, this is the
     compressed_size from the unnamed
     $DATA attribute.  NOTE: This is a
     multiple of the cluster size. */
  /* 30 */ qint64     data_size;
  /* Byte size of actual data in data
     attribute. */
  /* 38 */ FILE_ATTR_FLAGS file_attributes;
  /* Flags describing the file. */
/* 3c*/ union
  {
    /* 3c */ struct
    {
      /* 3c */ quint16    packed_ea_size;
      /* Size of the buffer needed to
         pack the extended attributes (EAs), if such are present. */
      /* 3e */ quint16    reserved;
      /* Reserved for alignment. */
    } __attribute__ ((__packed__));
    /* 3c */ quint32    reparse_point_tag;
    /* Type of reparse point,
       present only in reparse  points and only if there are no EAs. */
  } __attribute__ ((__packed__));
  /* 40 */ quint8     file_name_length;
  /* Length of file name in (Unicode) characters. */
  /* 41 */ FILE_NAME_TYPE_FLAGS file_name_type;
  /* Namespace of the file name. */
  /* 42 */ ntfschar   file_name[0];
  /* File name in Unicode. */
} __attribute__ ((__packed__)) FILE_NAME_ATTR;

/**
 * struct GUID - GUID structures store globally unique identifiers (GUID).
 *
 * A GUID is a 128-bit value consisting of one group of eight hexadecimal
 * digits, followed by three groups of four hexadecimal digits each, followed
 * by one group of twelve hexadecimal digits. GUIDs are Microsoft's
 * implementation of the distributed computing environment (DCE) universally
 * unique identifier (UUID).
 *
 * Example of a GUID:
 *	1F010768-5A73-BC91-0010-A52216A7227B
 */
typedef struct GUID
{
  quint32             data1;	/* The first eight hexadecimal digits of the GUID. */
  quint16             data2;	/* The first group of four hexadecimal digits. */
  quint16             data3;	/* The second group of four hexadecimal digits. */
  quint8              data4[8];	/* The first two bytes are the third group of four
				   hexadecimal digits. The remaining six bytes are the
				   final 12 hexadecimal digits. */
} __attribute__ ((__packed__)) GUID;

/**
 * struct OBJ_ID_INDEX_DATA - FILE_Extend/$ObjId contains an index named $O.
 *
 * This index contains all object_ids present on the volume as the index keys
 * and the corresponding mft_record numbers as the index entry data parts.
 *
 * The data part (defined below) also contains three other object_ids:
 *	birth_volume_id - object_id of FILE_Volume on which the file was first
 *			  created. Optional (i.e. can be zero).
 *	birth_object_id - object_id of file when it was first created. Usually
 *			  equals the object_id. Optional (i.e. can be zero).
 *	domain_id	- Reserved (always zero).
 */
typedef struct OBJ_ID_INDEX_DATA
{
  MFT_REF             mft_reference;	/* Mft record containing the object_id in
					   the index entry key. */
  union
  {
    struct
    {
      GUID                birth_volume_id;
      GUID                birth_object_id;
      GUID                domain_id;
    } __attribute__ ((__packed__));
    quint8              extended_info[48];
  } __attribute__ ((__packed__));
} __attribute__ ((__packed__)) OBJ_ID_INDEX_DATA;

/**
 * struct OBJECT_ID_ATTR - Attribute: Object id (NTFS 3.0+) (0x40).
 *
 * NOTE: Always resident.
 */
typedef struct OBJECT_ID_ATTR
{
  GUID                object_id;	/* Unique id assigned to the
					   file. */
  /* The following fields are optional. The attribute value size is 16
     bytes, i.e. sizeof(GUID), if these are not present at all. Note,
     the entries can be present but one or more (or all) can be zero
     meaning that that particular value(s) is(are) not defined. Note,
     when the fields are missing here, it is well possible that they are
     to be found within the $Extend/$ObjId system file indexed under the
     above object_id. */
  union
  {
    struct
    {
      GUID                birth_volume_id;	/* Unique id of volume on which
						   the file was first created. */
      GUID                birth_object_id;	/* Unique id of file when it was
						   first created. */
      GUID                domain_id;	/* Reserved, zero. */
    } __attribute__ ((__packed__));
    quint8              extended_info[48];
  } __attribute__ ((__packed__));
} __attribute__ ((__packed__)) OBJECT_ID_ATTR;

/**
 * struct VOLUME_NAME - Attribute: Volume name (0x60).
 *
 * NOTE: Always resident.
 * NOTE: Present only in FILE_Volume.
 */
typedef struct VOLUME_NAME
{
  ntfschar            name[0];	/* The name of the volume in Unicode. */
} __attribute__ ((__packed__)) VOLUME_NAME;

/**
 * enum VOLUME_FLAGS - Possible flags for the volume (16-bit).
 */
typedef enum VOLUME_FLAGS
{
  VOLUME_IS_DIRTY = const_cpu_to_le16 (0x0001),
  VOLUME_RESIZE_LOG_FILE = const_cpu_to_le16 (0x0002),
  VOLUME_UPGRADE_ON_MOUNT = const_cpu_to_le16 (0x0004),
  VOLUME_MOUNTED_ON_NT4 = const_cpu_to_le16 (0x0008),
  VOLUME_DELETE_USN_UNDERWAY = const_cpu_to_le16 (0x0010),
  VOLUME_REPAIR_OBJECT_ID = const_cpu_to_le16 (0x0020),
  VOLUME_CHKDSK_UNDERWAY = const_cpu_to_le16 (0x4000),
  VOLUME_MODIFIED_BY_CHKDSK = const_cpu_to_le16 (0x8000),
  VOLUME_FLAGS_MASK = const_cpu_to_le16 (0xc03f),
} __attribute__ ((__packed__)) VOLUME_FLAGS;

/**
 * struct VOLUME_INFORMATION - Attribute: Volume information (0x70).
 *
 * NOTE: Always resident.
 * NOTE: Present only in FILE_Volume.
 * NOTE: Windows 2000 uses NTFS 3.0 while Windows NT4 service pack 6a uses
 *	 NTFS 1.2. I haven't personally seen other values yet.
 */
typedef struct VOLUME_INFORMATION
{
  quint64             reserved;	/* Not used (yet?). */
  quint8              major_ver;	/* Major version of the ntfs format. */
  quint8              minor_ver;	/* Minor version of the ntfs format. */
  VOLUME_FLAGS        flags;	/* Bit array of VOLUME_* flags. */
} __attribute__ ((__packed__)) VOLUME_INFORMATION;

/**
 * struct DATA_ATTR - Attribute: Data attribute (0x80).
 *
 * NOTE: Can be resident or non-resident.
 *
 * Data contents of a file (i.e. the unnamed stream) or of a named stream.
 */
typedef struct DATA_ATTR
{
  quint8              data[0];	/* The file's data contents. */
} __attribute__ ((__packed__)) DATA_ATTR;

/**
 * enum INDEX_HEADER_FLAGS - Index header flags (8-bit).
 */
typedef enum INDEX_HEADER_FLAGS
{
  /* When index header is in an index root attribute: */
  SMALL_INDEX = 0,		/* The index is small enough to fit inside the
				   index root attribute and there is no index
				   allocation attribute present. */
  LARGE_INDEX = 1,		/* The index is too large to fit in the index
				   root attribute and/or an index allocation
				   attribute is present. */
  /*
   * When index header is in an index block, i.e. is part of index
   * allocation attribute:
   */
  LEAF_NODE = 0,		/* This is a leaf node, i.e. there are no more
				   nodes branching off it. */
  INDEX_NODE = 1,		/* This node indexes other nodes, i.e. is not a
				   leaf node. */
  NODE_MASK = 1,		/* Mask for accessing the *_NODE bits. */
} __attribute__ ((__packed__)) INDEX_HEADER_FLAGS;

/**
 * struct INDEX_HEADER -
 *
 * This is the header for indexes, describing the INDEX_ENTRY records, which
 * follow the INDEX_HEADER. Together the index header and the index entries
 * make up a complete index.
 *
 * IMPORTANT NOTE: The offset, length and size structure members are counted
 * relative to the start of the index header structure and not relative to the
 * start of the index root or index allocation structures themselves.
 */
typedef struct INDEX_HEADER
{
  /*  0 */ quint32    entries_offset;
  /* Byte offset from the INDEX_HEADER to first
     INDEX_ENTRY, aligned to 8-byte boundary.  */
  /*  4 */ quint32    index_length;
  /* Data size in byte of the INDEX_ENTRY's,
     including the INDEX_HEADER, aligned to 8. */
  /*  8 */ quint32    allocated_size;
  /* Allocated byte size of this index (block),
     multiple of 8 bytes. See more below.      */
  /* 
     For the index root attribute, the above two numbers are always
     equal, as the attribute is resident and it is resized as needed.

     For the index allocation attribute, the attribute is not resident 
     and the allocated_size is equal to the index_block_size specified 
     by the corresponding INDEX_ROOT attribute minus the INDEX_BLOCK 
     size not counting the INDEX_HEADER part (i.e. minus -24).
   */
  /* 12 */ INDEX_HEADER_FLAGS ih_flags;
  /* Bit field of INDEX_HEADER_FLAGS.  */
  /* 13 */ quint8     reserved[3];
  /* Reserved/align to 8-byte boundary. */
/* sizeof() == 16 */
} __attribute__ ((__packed__)) INDEX_HEADER;

/**
 * struct INDEX_ROOT - Attribute: Index root (0x90).
 *
 * NOTE: Always resident.
 *
 * This is followed by a sequence of index entries (INDEX_ENTRY structures)
 * as described by the index header.
 *
 * When a directory is small enough to fit inside the index root then this
 * is the only attribute describing the directory. When the directory is too
 * large to fit in the index root, on the other hand, two additional attributes
 * are present: an index allocation attribute, containing sub-nodes of the B+
 * directory tree (see below), and a bitmap attribute, describing which virtual
 * cluster numbers (vcns) in the index allocation attribute are in use by an
 * index block.
 *
 * NOTE: The root directory (FILE_root) contains an entry for itself. Other
 * directories do not contain entries for themselves, though.
 */
typedef struct INDEX_ROOT
{
  /*  0 */ ATTR_TYPES type;
  /* Type of the indexed attribute. Is
     $FILE_NAME for directories, zero
     for view indexes. No other values
     allowed. */
  /*  4 */ COLLATION_RULES collation_rule;
  /* Collation rule used to sort the
     index entries. If type is $FILE_NAME,
     this must be COLLATION_FILE_NAME. */
  /*  8 */ quint32    index_block_size;
  /* Size of index block in bytes (in the index allocation attribute). */
  /* 12 */ qint8      clusters_per_index_block;
  /* Size of index block in clusters 
     (in the index allocation attribute), when
     an index block is >= than a cluster,
     otherwise sectors per index block. */
  /* 13 */ quint8     reserved[3];
  /* Reserved/align to 8-byte boundary. */
  /* 16 */ INDEX_HEADER index;
  /* Index header describing the
     following index entries. */
/* sizeof()= 32 bytes */
} __attribute__ ((__packed__)) INDEX_ROOT;

#endif
