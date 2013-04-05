// stageDoc.h : interface of the CStageDoc class
//
/////////////////////////////////////////////////////////////////////////////
#define YO_HASH_VALUE 31
#define YO_HASH_SIZE 200

#define YO_DEVICE 1
#define YO_LIGHT 2
#define YO_ROBOT6 3
#define YO_ROTARY_TABLE 4
#define YO_GRIPPER 5
#define YO_BAR_CODE_READER 6
#define YO_SCALE 7
#define YO_TRACK 8
#define YO_TRAIN 9
#define YO_CONVEYOR 10
#define YO_CONVEYOR_PALLET 11
#define YO_BARRETT_HAND 12
#define YO_CAMERA 50

#define YO_DEVICE_PART 1
#define YO_TAG 2

#define YO_TRACK_LINE 1
#define YO_TRACK_CIRCLE 2
#define YO_TRACK_SWITCH 3
#define YO_TRACK_CROSS 4
#define YO_TRACK_FROM_TO 1
#define YO_TRACK_TO_FROM 0
#define YO_SWITCH_OPENED 1
#define YO_SWITCH_CLOSED 0
#define YO_TRACK_TOLERANCE 2.0     // default point tolerance in mm 

#define YO_RED 0
#define YO_GREEN 1
#define YO_BLUE 2
#define YO_ALPHA 3

#define YO_MODE_WORKCELL 0
#define YO_MODE_RECORD_SIM 1
#define YO_MODE_PLAY_SIM 2

#define YO_RENDER_FULL 0
#define YO_RENDER_LIGHT 1
#define YO_RENDER_NO_LIGHT 2
#define YO_RENDER_SAVE_WORKCELL 3
#define YO_RENDER_SAVE_DEVICE 4
#define YO_RENDER_LIGHT_VIEWPOINT 5
#define YO_RENDER_PICK_PART 6
#define YO_RENDER_PICK_PART_AND_TAG 7
#define YO_RENDER_QUICK 8
#define YO_RENDER_FLAT 9
#define YO_RENDER_POLYGON 10

#define YO_RENDER_MODE_WIREFRAME 0
#define YO_RENDER_MODE_POLYGON_FILLED 1
#define YO_RENDER_MODE_POLYGON_POINT 2
#define YO_RENDER_MODE_POLYGON_LINE 3
#define YO_RENDER_MODE_TEXTURE_POLYGON_FILLED 4
#define YO_RENDER_MODE_TEXTURE_POLYGON_POINT 5
#define YO_RENDER_MODE_TEXTURE_POLYGON_LINE 6

#define YO_ANALYSIS_MODE_NULL 0
#define YO_ANALYSIS_MODE_VERTEX 1
#define YO_ANALYSIS_MODE_POLYGON 2
#define YO_ANALYSIS_MODE_POLYGON_CENTER 3
#define YO_ANALYSIS_MODE_EDGE 4
#define YO_ANALYSIS_MODE_EDGE_CENTER 5
#define YO_ANALYSIS_MODE_PART 6
#define YO_ANALYSIS_MODE_DEVICE 7
#define YO_ANALYSIS_MODE_COORDINATE 8

#define YO_SNAP_COORDINATE 0
#define YO_SNAP_EDGE 1
#define YO_SNAP_EDGE_CENTER 2
#define YO_SNAP_PART 3
#define YO_SNAP_POLYGON 4
#define YO_SNAP_POLYGON_CENTER 5
#define YO_SNAP_VERTEX 6

#define YO_UNITS_MILLIMETERS 0
#define YO_UNITS_INCHES 1
#define YO_UNITS_FEET 2
#define YO_UNITS_METERS 3
#define YO_UNITS_KILOGRAMS 10
#define YO_UNITS_POUNDS 11

#define YO_UNDO_OFF 0
#define YO_UNDO_EYE_POSITION 1
#define YO_UNDO_PART_POSITION 2
#define YO_UNDO_TAG_POSITION 3
#define YO_UNDO_DEVICE_DELETE 4
#define YO_UNDO_PART_DELETE 5
#define YO_UNDO_PATH_DELETE 6
#define YO_UNDO_TAG_DELETE 7
#define YO_UNDO_FILE_REVERT 8
#define YO_UNDO_PART_UPDATE 9

#define YO_BAR_CODE_UPC_A 1
#define YO_BAR_CODE_UPC_E 2

#define YO_OPTION_PICK 1

#define YO_RENDER3D_MOTION_BLUR 0x1
#define YO_RENDER3D_ANTI_ALIAS 0x2
#define YO_RENDER3D_SHADOWS 0x4

#define YO_RENDER2D_NOISE 0x1

#define YO_RENDER_MOTION_BLUR_SET 1
#define YO_RENDER_MOTION_BLUR_RESTORE 2

#define YO_WIREFRAME 1
#define YO_POLYGON 2
#define YO_TEXTURE 3
#define YO_RENDER3D 4

#define YO_MAX_KNOTS 8    //getgdesc(GD_TRIMCURVE_ORDER) = 8
#define YO_MAX_ORDER 8      // getgdesc(GD_NURBS_ORDER) = 8

#define YO_MAX_EFFECT_PROPS 12          // must be >= 8

#define YO_MIN(x, y)  (((x) < (y)) ? (x) : (y))
#define YO_MAX(x, y)  (((x) > (y)) ? (x) : (y))
#define YO_DOT_PRODUCT(v1, v2)  (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])

#define YO_MOTION_ANCHOR 1
#define YO_MOTION_CONTROL 2
#define YO_MOTION_HOLD 3

#define YO_MOTION_EFFECT_MODIFIED_ALL 99

#define YO_STOP 0
#define YO_PLAY 1
#define YO_PAUSE 2

#define YO_TXYZ_TXYZ 0
#define YO_TXYZ_TXZY 1
#define YO_TXYZ_TYXZ 2
#define YO_TXYZ_TYZX 3
#define YO_TXYZ_TZXY 4
#define YO_TXYZ_TZYX 5
#define YO_TXYZ_XYZT 6
#define YO_TXYZ_XZYT 7
#define YO_TXYZ_YXZT 8
#define YO_TXYZ_YZXT 9
#define YO_TXYZ_ZXYT 10
#define YO_TXYZ_ZYXT 11

#define YO_TRANSPARANT_OPAQUE 0

#define YO_RADIANS_TO_DEGREES 57.2957795131
#define YO_DEGREES_TO_RADIANS 0.017453293
#define YO_PI (180.0 / 57.2957795131)
#define YO_CONVEYOR_PALLET_WIDTH 328.612    // in mm
#define YO_CONVEYOR_TRANSVERSE_LIFT_TIME 0.4  // in sec
#define YO_CONVEYOR_TRANSVERSE_LIFT_HEIGHT 9.5  // in mm
#define YO_CONVEYOR_SEGMENT 1
#define YO_CONVEYOR_SENSOR 2
#define YO_CONVEYOR_STOP_GATE 3
#define YO_CONVEYOR_TRANSVERSE_LIFT 4
#define YO_SCAN_DISTANCE 700.0

#define YO_DEFAULT_GRID_VISIBLE TRUE
#define YO_DEFAULT_GRID_SPACING 1000
#define YO_DEFAULT_GRID_LENGTH 20000
#define YO_DEFAULT_GRID_WIDTH 15000
#define YO_DEFAULT_GRID_RED 255
#define YO_DEFAULT_GRID_GREEN 255
#define YO_DEFAULT_GRID_BLUE 0

#define YO_DEFAULT_SUN_ALTITUDE 45.0
#define YO_DEFAULT_SUN_AZIMUTH 0.0
#define YO_DEFAULT_SUN_INTENSITY 0.75
#define YO_DEFAULT_LIGHTING_TWO_SIDED 0

#define YO_DEFAULT_RENDER_ANTI_ALIAS 0
#define YO_DEFAULT_RENDER_BOUNDING_BOX 0
#define YO_DEFAULT_RENDER_FRAMES_PER_SECOND 30
#define YO_DEFAULT_RENDER_MOTION_BLUR_ITERATIONS 16

#define YO_DEFAULT_NETWORK_PORT 1650


class CStageSrvrItem;
// Forward Declaration of data structure classes
class CStageDevice;
class CStageLight;
class CStageRobot6;
class CStageRotaryTable;
class CStageGripper;
class CStageBarrettHand;
class CStageRotateInfo;
class CStageBarCodeReader;
class CStageScale;
class CStageTrain;
class CStageCamera;
class CStageTrackSeg;
class CStageConveyor;
class CStageConveyorSegment;
class CStageConveyorPallet;
class CStageConveyorSensor;
class CStageConveyorTransverseLift;
class CStageConveyorStopGate;
class CStagePart;
class CStageMotion;
class CStageEffect;
class CStageScore;
class CStageStack;
class CStageEye;
class CStageEyeView;
class CStageEyeScore;
class CStageEyeMotion;
class CStageVertexList;
class CStageVertices;
class CStageNormals;
class CStagePolygonList;
class CStagePolygon;
class CStageTexture;
class CStageTextureCoords;
class CGLImage;
class CStagePath;
class CStageTag;
class CStageSocket;
class CStageCommand;
//class CStageThreadPlay;
class CStageUndo;

class CStageDoc : public COleServerDoc
{

//protected: // create from serialization only
public:
	CStageDoc();
	DECLARE_DYNCREATE(CStageDoc)

// Attributes
public:
	CStageSrvrItem* GetEmbeddedItem()
		{ return (CStageSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStageDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Stage helper functions
public:
	BOOL YoInsertDevice(CStageDevice *, CStagePart *);
	BOOL YoAttachDevice(CStagePart *);
	void YoGetUniqueDeviceName(char *);
	void YoGetUniquePathName(char *);
	void YoMessage(char *);
	BOOL YoImportDevice(char *, char *);
	void YoCloneDevice(char *);
	void YoDetachDevice(void);
	void YoDeleteDevice(void);
	void YoDeletePart(void);
	void YoDeletePath(CStageTag *);
	void YoDeleteTag();
	BOOL YoModelMatrixOfCurrentPart(GLdouble m[16]);
	BOOL YoModelMatrixOfCurrentTag(void);
	BOOL YoInsertPart(CStageDevice *, CStagePart *);
	BOOL YoInsertEffect(CStageEffect *, CStagePart *);
	BOOL YoInsertPartMotion(CStageMotion *, CStagePart *);
	void YoInsertEyeMotion(CStageEyeMotion *);
	void YoLinkTrackSegs(void);
	class CStageDevice* YoDeviceHashLookup(char *);
	class CStagePath* YoPathHashLookup(char *);
	class CStageEyeView* YoEyeViewHashLookup(char *);
	void YoCrossProduct(GLdouble *, GLdouble *, GLdouble *);
	BOOL YoRayTriangleIntersect(double orig[3], double dir[3],
		double vert0[3], double vert1[3], double vert2[3],
		double *t, double *u, double *v);
	BOOL YoTriangleTriangleIntersect(double V0[3], double V1[3], double V2[3],
		double U0[3], double U1[3], double U2[3]);
	BOOL YoCoplanerTriangleTriangle(double N[3], double V0[3], double V1[3], double V2[3],
		double U0[3], double U1[3], double U2[3]);
	void YoNormalize(GLdouble *);
	void YoMatrixInverse(GLdouble[16], GLdouble[16]);
	void YoTranslateRotateValues(GLdouble[16], GLdouble[3], GLdouble[3]);
	void YoPartBoundingBox(GLdouble *);
	class CStagePart* YoPartLookup(CStageDevice *, char *);
	BOOL YoIsChild(CStageDevice *, CStageDevice *);
	BOOL YoIsChild(CStagePart *, CStagePart *);
	GLint YoGetNewDisplayListID(CStagePart *, CStageTag *);
	class CStageDevice* YoPopDevice(void);
	void YoPushDevice(CStageDevice *);
	void YoFreeDevice(void);
	BOOL YoAllStackDevicesNull(void);
	class CStagePart* YoPopPart(void);
	class CStagePart* YoPopPart(CStageStack **);
	void YoPushPart(CStagePart *);
	void YoPushPart(CStageStack **, CStagePart *);
	void YoFreePart(void);
	BOOL YoAllStackPartsNull(void);
	void YoUpdateScore(void);
	void YoUpdatePartScore(CStagePart *);
	void YoFreeScore(CStagePart *);
	void YoFreeEyeScore(void);
	void YoFreeEyeList(void);
	void YoRestoreCurrentScore(void);
	BOOL YoHandleCommand(char *buf);
	void YoHandleMotion(CStagePart *);
	void YoHandleEyeMotion(void);
	void YoPause(void);
	void YoRewind(void);
	void YoExtractTranslateRotate(GLdouble *, GLdouble *, GLdouble *);
	void YoPlay(void);
	void YoMove(void);
	void YoHaltAllMotion(void);
	UINT YoMakeCurrentDevicePartTag(CPoint);
	BOOL YoPointOnCurrentPart(CPoint);
	BOOL YoGetClosestPolygon(CPoint);
	BOOL YoDeviceHashInstall(CStageDevice *);
	BOOL YoPathHashInstall(CStagePath *);
	BOOL YoEyeViewHashInstall(CStageEyeView *);
	unsigned YoHash(char *, unsigned, unsigned);
	BOOL YoFreeWorkcell(void);
	void YoValidateRotate(GLdouble *);
	void YoMakeDisplayLists(GLint);
	BOOL YoSocketInit(void);
	void YoUnitScaleFactor(void);
	BOOL YoReadWorkcell(FILE *);
	BOOL YoWriteWorkcell(LPCTSTR);
	BOOL YoWriteViewBitmap(char *);
	void YoEStop(void);
	void YoChangeTime(SYSTEMTIME *, double);

private:
	//BOOL YoReadWorkcell(CArchive&);
	BOOL YoDeviceHashInit(void);
	BOOL YoPathHashInit(void);
	BOOL YoEyeViewHashInit(void);
	BOOL YoPickInit(void);

public:
	unsigned int m_alphaBlending[2];
	GLint m_alphaFunction;
	GLfloat m_alphaFunctionRef;
	float m_grid[7];   // on-off, spacing, length, width, r, g, b
	GLint m_lighting[6];  // local viewer, two-sided, r, g, b, a
	BOOL m_worldCoordinateFrame;
	BOOL m_boundingBox;
	//BOOL m_autoSocketServer;
	GLenum m_fog[2];
	GLfloat m_fogParameters[8];
	GLdouble m_splineResolution;
	//GLdouble m_eye[9];
	//GLdouble m_clipFront;
	//GLdouble m_clipRear;
	//GLdouble m_fieldOfView;
	//GLdouble m_aspectRatio;
	GLint m_isMovement;
	GLint m_framesPerSecond;
	BOOL m_realTime;
	BOOL m_antiAlias;
	BOOL m_smoothShading;
	BOOL m_outputBitmap;
	GLint m_shutterSpeed;
	double m_timeCurrent;
	double m_timeEnd;
	double m_timePause;
	double m_timeSleepTotal;
	BOOL m_scriptFastForward;
	SYSTEMTIME m_gmTimeStart;
	SYSTEMTIME m_gmTime;
	BOOL m_motionEffectModified;
	BOOL m_timeModified;
	GLint m_displayListID;
	GLint m_numberLightsOn;
	GLint m_animationState;
	GLint m_render3d;
	GLint m_timeMotionBlur;
	GLint m_motionBlurIterations;
	int m_accumCount;
	UINT m_shadowSensitivity;
	GLint m_quickMode;
	GLint m_mode;
	GLint m_renderMode;
	GLint m_units;
	GLdouble m_unitScaleFactor;
	float m_sunAltitude;
	float m_sunAzimuth;
	float m_sunIntensity;

	char m_fileName[256];
	char m_scriptName[256];
	CStageDevice *m_deviceList;
	CStageLight *m_lightList;
	CStageDevice *m_deviceHash[YO_HASH_SIZE];
	CStagePath *m_pathHash[YO_HASH_SIZE];
	int m_numberOfPaths;
	CStageEyeView *m_eyeViewHash[YO_HASH_SIZE];
	CStageDevice *m_currentDevice;
	BOOL m_deviceBeingAttached;
	CStagePart *m_tempAttachedFromPart;  // needed during device translation mode
	CStageStack *m_deviceStack;
	CStagePart *m_currentPart;
	CStageTag *m_currentTag;
	int m_currentPolygonIndex;
	int m_closestVertexIndex;
	GLdouble m_modelViewOfCurrentPart[16];
	GLdouble m_mTag[16];
	GLdouble m_mSnapTo[16];
	int m_snapToViewPart;
	int m_snapToViewTag;
	CStageStack *m_partStack;
	CStageTexture *m_textureList;
	CStageTexture *m_textureHash[YO_HASH_SIZE];
	CStagePart *m_pickPart[YO_HASH_SIZE];
	CStageTag *m_pickTag[YO_HASH_SIZE];
	CStageEye *m_eyeList;
	CStageCamera *m_camera;
	CStageUndo *m_undo;
	//CWinThread *m_threadRender;
	//CStageDoc *m_threadPlay;

	CStageCommand *m_commandList;
	CStageCommand *m_currentCommand;
	CStageSocket *m_acceptSocket;
	CStageSocket *m_socket;
	u_short m_port;
	BOOL m_resumeMove;
	//CRITICAL_SECTION CStageDoc::m_criticalSection;


	//CTypedPtrList<CObList, CObList*> m_deviceList;
	//CTypedPtrList<CObList, CObList*> m_currentDevice;
	//CTypedPtrList<CObList, CStagePart*> m_currentPart;
	//CTypedPtrList<CObList, CStageTexture*> m_textureList;
	//CTypedPtrList<CObList, CStageTexture*> m_textureHash[YO_TEXTURE_HASHSIZE];
};


// Stage data structure classes
class CStageStack : public CObject
{

// Attributes
public:
	LPVOID m_ptr;
	CStageStack *m_next;
	
// Operations
};


class CStageDevice: public CObject
{
public:
	CStageDevice(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
	CStageDevice();
	//DECLARE_SERIAL(CStageDevice)

// Attributes
public:
	CStageDoc *m_pDoc;
	UINT m_type;
	char m_name[64];
	char m_parent[64];
	double m_min[3];
	double m_max[3];
	double m_scale[3];
	BOOL m_visible;
	GLdouble m_mass;
	char m_barCode[32];
	//float m_mat[21];
	CStagePart *m_ptrPart;
	CStageDevice *m_nextHash;
	//BOOL m_stackBit;
	//CStageDevice *m_nextStack;
	CStageDevice *m_right;
	CStageDevice *m_down;
	CStageDevice *m_left;
	CStageDevice *m_up;
	CStagePart *m_attachedFromPart;
	GLdouble m_mAttach[16];


	//CTypedPtrList<CObList, CStagePart*> m_ptrPart;
	//CObList m_right;
	//CObList m_down;
	//CObList m_left;
	//CObList m_up;

// Operations
public:
	BOOL YoReadDevice(FILE *, CStageDevice *);
	BOOL YoInitDevice(CStageDevice *);
	BOOL YoHandleCommand(char ibuf[], char obuf[]);
};

class CStageLight: public CStageDevice
{
public:
	CStageLight(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStageLight();
protected:
	//DECLARE_SERIAL(CStageLight)

// Attributes
public:
	GLenum	m_target;
	BOOL	m_enabled;
	BOOL	m_changing;
	BOOL	m_pointSource;
	GLfloat m_intensity;
	GLfloat m_intensityStart;
	GLfloat m_intensityFinal;
	SYSTEMTIME m_gmTimeStart;
	GLdouble m_timeStart;
	GLdouble m_timeOfMove;
	//GLfloat	m_ambient[4];
	//GLfloat m_diffuse[4];
	//GLfloat m_specular[4];
	//GLfloat m_position[4];
	//GLenum	m_parameterName;
	//GLfloat	m_spotExponent;
	GLfloat	m_spotCutoff;
	GLfloat	m_attenuation[3];
	GLfloat *m_shadowMap;
	GLdouble m_modelView[16];
	CStageLight *m_ptrLight;
	//CTypedPtrList<CObList, CStageLight*> m_ptrLight;

// Operations
public:
	BOOL YoReadLight(FILE *, CStageLight *);
	BOOL YoGetLight(void);
	void YoFreeLight(void);
	BOOL YoHandleCommand(char *buf);
	void YoCalculateLightIntensity(void);
};

class CStageRobot6: public CStageDevice
{
public:
	CStageRobot6(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL YoHandleCommand(char *);
	BOOL YoReadRobot6(FILE *, CStageRobot6 *);
	BOOL YoRotateJoint(CStagePart *);
	BOOL YoMoveTo(GLdouble[16]);
	BOOL YoCalculateTimeOfRotation(void);
	BOOL YoCalculateJointAngles(void);
	BOOL YoInverseKinematics(GLdouble m[16], GLdouble j[7][4]);
	BOOL YoStraightLineMotion(double);
	void YoTagOnTcf(void);

protected:
	//DECLARE_SERIAL(CStageRobot6)

// Attributes
public:
	GLdouble m_j[7];			// j[0] not used
	GLdouble m_jStart[7];
	GLdouble m_jFinal[7];
	GLdouble m_mStart[16];		// TCF matrix when move starts
	GLdouble m_mFinal[16];		// TCF matrix at move to point
	SYSTEMTIME m_gmTimeStart;
	GLdouble m_timeStart;
	GLdouble m_timeOfMove;
	BOOL m_lefty;					// TRUE if lefty, FALSE if righty
	BOOL m_elbowUp;					// TRUE if elbow up, FALSE if elbow down
	BOOL m_wristFlipped;			// TRUE if flipped
	GLdouble m_jMinMax[7][2];
	GLdouble m_jMaxAccelMaxSpeed[7][2];
	GLdouble m_jMinAccelTime[7];
	GLdouble m_tcpOffset[6];      // tx, ty, tz, rx, ry, rz
	GLint m_speed;
	GLdouble m_minAccelTime;
	GLdouble m_accelTime;
	GLdouble m_accelDistance;
	GLdouble m_totalDistance;
	BOOL m_jointInterpolation;    // if false, linear
	GLdouble m_maxScrewSpeed;
	GLdouble m_maxScrewAccel;
	GLdouble m_maxToolSpeed;
	GLdouble m_maxToolAccel;
	GLdouble m_cartesianSpace[6]; // tx, ty, tz, rx, ry, rz
	GLdouble m_home[7];
	BOOL m_moving;

// Operations
public:

};

class CStageRotaryTable: public CStageDevice
{
public:
	CStageRotaryTable(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStageRotaryTable();
	BOOL YoHandleCommand(char *, char *);
	BOOL	YoHandleSim(char *);
	BOOL	YoRotateTable(CStagePart *);
	void	YoGetRTSettings(void);
	double	YoCalculateTimeOfRotation(void);
	double	YoCalculateTimeToHome(void);
	long	YoCalculateRTPosition(void);
	void	YoStopTable(void);
	void	YoEStop(void);
	BOOL	YoReadRotaryTable(FILE *, CStageRotaryTable *);


// Attributes
public:
	BOOL m_rotating;
	long m_endPosition;
	long m_currentPosition;
	long m_encoderResolution;
	BOOL m_directionPositive;
	float m_velocity;
	float m_acceleration;
	long m_distance;
	BOOL m_positionAbsolute;
	BOOL m_stoppingTable;
	BOOL m_simRequestDone;
	CStageRotateInfo *m_ptrRotateInfo;
};

class CStageRotateInfo: public CObject
{
public:
	CStageRotateInfo()
	{
		m_next = NULL;
		m_endOfHome = FALSE;
	};
	float m_velocity;
	float m_acceleration;
	long m_startPosition;
	long m_endPosition;
	BOOL m_directionPositive;
	SYSTEMTIME m_gmTimeStart;
	double m_timeStart;
	double m_timeOfRotation;
	BOOL m_endOfHome;
	CStageRotateInfo *m_next;
};


class CStageGripper: public CStageDevice
{
public:
	CStageGripper(CStageDoc *pDoc) {m_pDoc = pDoc;};
	void	YoOpenGripper(void);
	void	YoCloseGripper(char deviceName[64]);
	void	YoCloseGripper(void);
	CStageDevice *YoFindDeviceToGrip(void);
	BOOL	YoReadGripper(FILE *, CStageGripper *);
	BOOL YoHandleCommand(char *buf);
	BOOL YoPositionFinger(CStagePart *);

// Attributes
public:
	BOOL m_typeTranslating;
	BOOL m_gripping;
	GLdouble m_displacementOpen;
	GLdouble m_displacementClose;
};


class CStageBarCodeReader: public CStageDevice
// Note: construct bar code reader so that the coordinate
// system of the last part designates beam direction (z-axis)
// and spread (x-axis).
{
public:
	CStageBarCodeReader(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL YoReadBarCodeReader(FILE *, CStageBarCodeReader *);
	void YoRenderScan(void);
	BOOL YoHandleCommand(char *buf);
	CStageDevice *YoGetScan();

// Attributes
public:
	BOOL m_scanning;
	GLdouble m_scanDistance;
	char m_barCode[32];
};


class CStageScale: public CStageDevice
{
public:
	CStageScale(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL	YoReadScale(FILE *, CStageScale *);
	BOOL YoHandleCommand(char *buf);
	CStageDevice *YoGetMass();

// Attributes
public:
	BOOL m_weighing;
	int m_units;
	//GLfloat m_mass;
};

class CStageTrain: public CStageDevice
{
public:
	CStageTrain(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL YoHandleCommand(char *buf);
	BOOL YoReadTrain(FILE *, CStageTrain *);
	void YoCalculateTrainPosition(void);
	void YoAnimateTrain(void);
	BOOL YoEStop();

// Attributes
public:
	//char m_trackName[64];		// associate train with a given track name
	CStageTrackSeg *m_ptrTrackSeg;
	//int m_attachTrackSeg;		// number of track segment where train is attached
	//double m_attachRelativePosition;
	BOOL m_moving;
	BOOL m_directionPositive;
	BOOL m_changingDirection;
	CStageTrackSeg *m_ptrTrackSegEnd;
	double m_relativePositionEnd;
	double m_totalDistance;
	//double m_endPosition[2];
	//double m_currentPosition[2];
	double m_relativePosition;       // number between 0.0 (from) and 1.0 (to)
	//BOOL m_directionPositive;
	double m_velocity;				// in mm / sec
	double m_acceleration;			// in mm / sec2
	double m_initialVelocity;
	double m_finalVelocity;
	double m_reverseFinalVelocity;
	double m_curVelocity;
	SYSTEMTIME m_gmTimeStart;
	double m_timeStart;
	//double m_heading;				// in degrees
	BOOL m_trackOrientation;		// FROM_TO or TO_FROM
	BOOL m_stoppingTrain;
	BOOL m_simRequestDone;
	//double length;					// length of train in mm
};

class CStageCamera: public CStageDevice
{
public:
	CStageCamera(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
	//DECLARE_SERIAL(CStageCamera)

// Attributes
public:
	BOOL	m_enabled;
	double	m_fieldOfView;
	//double	m_aspectRatio;
	double	m_clipRear;
	double	m_clipFront;
	double  m_fStop;
	CStageCamera *m_ptrCamera;
	//CTypedPtrList<CObList, CStageCamera*> m_ptrCamera;

// Operations
public:
	BOOL YoReadCamera(FILE *, CStageCamera *);
	BOOL YoHandleCommand(char *buf);
	BOOL YoPositionCamera(void);

};

class CStageTrackSeg: public CObject
{
public:
	UINT	m_type;
	double	m_from[2];				// starting position
	double	m_to[2];				// ending position
	double	m_switch[2];			// ending position of switch segment
	BOOL	m_switchStatus;			// open (going toward switch) or closed
	//UINT	switchStatusMessageID;	// switch status in message[]
	//UINT	switchStatusMessageBit;	// shift left n bits (1-4)
	double	m_distance;
	double  m_switchDistance;
	double	m_radius;				// radius of curvature for circular segments
	double	m_heading;				// in degrees (x axis = 0 deg)
	double	m_angle;				// sweep out n deg track segment
	CStagePart *m_ptrPart;
	//struct	track_node *next;	// next track in track list
	CStageTrackSeg *m_ptrFrom;		// link from start to track sharing endpoint
	CStageTrackSeg *m_ptrTo;		// link from finish to track sharing endpoint
	CStageTrackSeg *m_ptrSwitch;	// link from switch segment to track sharing endpoint
	//struct sensor_node *ptrSensor;// pointer to sensor on this track segment
};


class CStageBarrettHand: public CStageDevice
{
public:
	CStageBarrettHand(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL YoHandleCommand(char *buf);
	BOOL YoEStop(void);
	BOOL YoReadBarrettHand(FILE *, CStageBarrettHand *);
	BOOL YoCalculateBHPosition();
	BOOL YoPositionFinger(CStagePart *);
	void YoOpenHand(void);
	void YoCloseHand(char deviceName[64]);
	CStageDevice *YoFindDeviceToGrab();

// Attributes
public:
	int m_moving;
	double m_velocity;
	BOOL m_gripping;
	BOOL m_spreading;
	double m_spread;  // 0.0 to 180.0
	double m_fingerFixed[3];
	double m_fingerLeft[3];
	double m_fingerRight[3];
	double m_fingerFixedStart[3];
	double m_fingerLeftStart[3];
	double m_fingerRightStart[3];
	double m_fingerFixedEnd[3];
	double m_fingerLeftEnd[3];
	double m_fingerRightEnd[3];
	SYSTEMTIME m_gmTimeStart;
	double m_timeStart;

};

class CStageConveyor: public CStageDevice
{
public:
	CStageConveyor(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStageConveyor();
	BOOL YoHandleSim(char *buf);
	BOOL YoEStop();  // immidiately ceases all motion
	BOOL YoReadConveyor(FILE *, CStageConveyor *);
	BOOL YoWriteConveyor(FILE *, CStagePart *);
	BOOL YoInsertPallet(CStageConveyorPallet *);  // Called when the segment is not known
	BOOL YoInsertPallet(CStageConveyorPallet *, CStageConveyorSegment *);
	BOOL YoRemovePallet(CStageConveyorPallet *);
	BOOL YoTransferPallet(CStageConveyorPallet *, CStageConveyorSegment *);
	//BOOL YoLinkPallets();
	//BOOL YoLinkPallets(CStageConveyorSegment *);
	BOOL YoInsertSegment(CStageConveyorSegment *);
	BOOL YoInsertSensor(CStageConveyorSensor *);
	BOOL YoInsertStopGate(CStageConveyorStopGate *);
	BOOL YoInsertTransverseLift(CStageConveyorTransverseLift *);
	BOOL YoCheckForPalletCollision(CStageConveyorSegment **, double *, double *, double *);
	BOOL YoCheckTransverseLift(CStageConveyorSegment *, double *);
	int YoFind(CStagePart *, CStageConveyorSegment **, CStageConveyorSensor **,
		CStageConveyorStopGate **, CStageConveyorTransverseLift **);
	CStageConveyorSegment *YoFindSegment(double *, double *, double *);
	CStageConveyorSegment *YoFindSegment(CStagePart *);
	CStageConveyorSensor *YoFindSensor(CStagePart *);
	CStageConveyorStopGate *YoFindStopGate(CStagePart *);
	CStageConveyorTransverseLift *YoFindTransverseLift(CStagePart *);
	BOOL YoSetStopGates();
	BOOL YoClone(CStageConveyor *);
	BOOL YoClone(CStagePart *, CStagePart *);
	BOOL YoCalculateEndPositionOfPallets();
	double YoCalculateEndPositionOfPallets(CStageConveyorSegment *);
	BOOL YoCalculatePositionOfPallets();
	BOOL YoCalculatePositionOfPallets(CStageConveyorSegment *);
	BOOL YoSetStartPositionOfPallets();
	BOOL YoSetStartPositionOfPallets(CStageConveyorSegment *);
	BOOL YoUpdatePalletGraphicsPosition(CStageConveyorPallet *);
	BOOL YoSafeLift(CStageConveyorTransverseLift *, BOOL);
	BOOL YoIllegalMove(CStageConveyorSegment *, double);
	BOOL YoTransverseLiftsInMotion(CStageConveyorSegment *);
	void YoCheckSensors();


// Attributes
public:
	double m_offset[3];			// offset from base part coord to m_from of first conveyor segment
	int m_moving;
	CStageConveyorSegment *m_ptrSegment;
	//CStageConveyorPallet *m_ptrPallet;
	//CStageConveyorSensor *m_ptrSensor;
	//CStageConveyorStopGate *m_ptrStopGate;
	//CStageConveyorTransverseLift *m_ptrTransverseLift;
};

class CStageConveyorSegment: public CObject
{
public:
	CStageConveyorSegment() 
	{
		m_from[0] = 0.0f;
		m_from[1] = 0.0f;
		m_from[2] = 0.0f;
		m_to[0] = 0.0f;
		m_to[1] = 0.0f;
		m_to[2] = 0.0f;
		m_distance = 0.0f;
		m_curVelocity = 0.0f;
		m_maxVelocity = 0.0f;
		m_initialVelocity = 0.0f;
		m_finalVelocity = 0.0f;
		m_reverseFinalVelocity = 0.0f;
		m_acceleration = 0.0f;
		m_moving = FALSE;
		m_speed = 0.0f;
		m_relSpeed = 50.0f;
		m_directionForward = TRUE;
		m_changingDirection = FALSE;
		m_ptrPart = NULL;
		m_ptrNextSegment = NULL;
		m_ptrPrevSegment = NULL;
		m_ptrPallet = NULL;
		m_ptrLastPallet = NULL;
		m_ptrSensor = NULL;
		m_ptrLastSensor = NULL;
		m_ptrStopGate = NULL;
		m_ptrLastStopGate = NULL;
		m_ptrTransverseLift = NULL;
		m_ptrLastTransverseLift = NULL;
	};
// Attributes
public:
	double m_from[3];				// x, y, z starting position (at pallet center)
	double m_to[3];					// ending position
	double m_distance;
	double m_curVelocity;			// Note: all velocities are positive
	double m_maxVelocity;
	double m_origMaxVelocity;
	double m_initialVelocity;
	double m_finalVelocity;
	double m_reverseFinalVelocity;
	double m_acceleration;
	double m_origAcceleration;
	SYSTEMTIME m_gmTimeStart;
	double m_timeStart;
	double m_stoppingTime;
	BOOL m_moving;
	double m_speed;					// 0.0 to 1.0
	double m_relSpeed;				// 0.0 to 100.0 used in dialog window only
	double m_origRelSpeed;
	BOOL m_directionForward;
	BOOL m_origDirectionForward;
	BOOL m_changingDirection;
	CStagePart *m_ptrPart;
	CStageConveyorSegment *m_ptrNextSegment;
	CStageConveyorSegment *m_ptrPrevSegment;
	CStageConveyorPallet *m_ptrPallet;
	CStageConveyorPallet *m_ptrLastPallet;
	CStageConveyorSensor *m_ptrSensor;
	CStageConveyorSensor *m_ptrLastSensor;
	CStageConveyorStopGate *m_ptrStopGate;
	CStageConveyorStopGate *m_ptrLastStopGate;
	CStageConveyorTransverseLift *m_ptrTransverseLift;
	CStageConveyorTransverseLift *m_ptrLastTransverseLift;
};

class CStageConveyorPallet: public CStageDevice
{
public:
	CStageConveyorPallet(CStageDoc *pDoc) {m_pDoc = pDoc;};
	BOOL YoReadConveyorPallet(FILE *, CStageConveyorPallet *);
// Attributes
public:
	double m_startPosition[3];
	double m_origStartPosition[3];
	double m_position[3];
	double m_origPosition[3];  // used for conveyor dialog
	double m_endPosition[3];
	double m_origEndPosition[3];
	double m_relativePosition;
	double m_origRelativePosition;
	double m_distance;
	double m_origDistance;
	BOOL m_moving;
	CStageConveyorPallet *m_ptrNextPallet;
	CStageConveyorPallet *m_ptrPrevPallet;
	CStageConveyorSegment *m_ptrSegment;
	CStageConveyorSegment *m_ptrOrigSegment;  // used for conveyor dialog
};

class CStageConveyorSensor: public CObject
{
public:
	CStageConveyorSensor() 
	{
		m_position[0] = 0.0f;
		m_position[1] = 0.0f;
		m_position[2] = 0.0f;
		m_ptrPart = NULL;
		m_ptrNextSensor = NULL;
		m_ptrPrevSensor = NULL;
		m_ptrSegment = NULL;
		m_ptrPallet = NULL;
	};
// Attributes
public:
	double m_position[3];
	double m_relativePosition;
	CStagePart *m_ptrPart;
	CStageConveyorSensor *m_ptrNextSensor;
	CStageConveyorSensor *m_ptrPrevSensor;
	CStageConveyorSegment *m_ptrSegment;
	CStageConveyorPallet *m_ptrPallet;
};

class CStageConveyorStopGate: public CObject
{
public:
	CStageConveyorStopGate() 
	{
		m_position[0] = 0.0f;
		m_position[1] = 0.0f;
		m_position[2] = 0.0f;
		m_relativePosition = 0.0f;
		m_forward = TRUE;
		m_stop = FALSE;
		m_origStop = FALSE;
		m_ptrPart = NULL;
		m_ptrNextStopGate = NULL;
		m_ptrPrevStopGate = NULL;
		m_ptrSegment = NULL;
		m_ptrPallet = NULL;
	};
// Attributes
public:
	double m_position[3];
	double m_relativePosition;
	BOOL m_forward;
	BOOL m_stop;
	BOOL m_origStop;
	CStagePart *m_ptrPart;
	CStageConveyorStopGate *m_ptrNextStopGate;
	CStageConveyorStopGate *m_ptrPrevStopGate;
	CStageConveyorSegment *m_ptrSegment;
	CStageConveyorPallet *m_ptrPallet;
};

class CStageConveyorTransverseLift: public CObject
{
public:
	CStageConveyorTransverseLift() 
	{
		m_position[0] = 0.0f;
		m_position[1] = 0.0f;
		m_position[2] = 0.0f;
		m_relativePosition = 0.0f;
		m_up = FALSE;
		m_origUp = FALSE;
		m_inMotion = FALSE;
		m_forwardBlocking = TRUE;
		m_reverseBlocking = FALSE;
		m_ptrPart = NULL;
		m_ptrNextTransverseLift = NULL;
		m_ptrPrevTransverseLift = NULL;
		m_ptrSegment = NULL;
		m_ptrTransverseSegment = NULL;
		m_ptrMirrorTransverseLift = NULL;
		m_ptrPallet = NULL;
	};
// Attributes
public:
	double m_position[3];
	double m_relativePosition;
	BOOL m_up;
	BOOL m_origUp;
	BOOL m_inMotion;
	BOOL m_forwardBlocking;
	BOOL m_reverseBlocking;
	SYSTEMTIME m_gmTimeStart;
	double m_timeStart;
	CStagePart *m_ptrPart;
	CStageConveyorTransverseLift *m_ptrNextTransverseLift;
	CStageConveyorTransverseLift *m_ptrPrevTransverseLift;
	CStageConveyorSegment *m_ptrSegment;
	CStageConveyorSegment *m_ptrTransverseSegment;
	CStageConveyorTransverseLift *m_ptrMirrorTransverseLift;
	CStageConveyorPallet *m_ptrPallet;
};


class CStagePart: public CObject
{
public:
	CStagePart(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
//	DECLARE_SERIAL(CStagePart)

// Attributes
public:
	CStageDoc *m_pDoc;
	//GLint m_displayType;
	GLint m_displayListID;
	GLint m_wireframeDisplayListID;  // not used
	CStageVertexList *m_vertexList;
	GLint m_numberPolygons;
	GLint m_numberVertices;
	CStagePolygonList *m_polygonList;
	char m_deviceName[64];
	char m_partName[64];
	char m_partParent[64];
	char m_partFile[128];
	BOOL m_originVisible;
	GLdouble m_altOrigin[16];   // matrix multiplication required to get from an alternative origin back to the original origin
	BOOL m_altOriginDisplayed;
	GLdouble m_translate[3];
	GLdouble m_rotate[3];
	GLdouble m_modelMatrix[16];  // model matrix at a given graphic update
	UINT m_txyz;
	GLdouble m_min[3];
	GLdouble m_max[3];
	CStagePart *m_right;
	CStagePart *m_down;
	CStagePart *m_left;
	CStagePart *m_up;
	CStageDevice *m_attachedDevice;
	CStagePart *m_pick;
	BOOL m_motionEffectModified;
	CStagePath *m_path;
	CStageTrackSeg *m_ptrTrackSeg;
	CStageMotion *m_motion;
	CStageEffect *m_effect;
	CStageScore *m_score;
	CStageScore *m_currentScore;
	UINT m_renderMode;
	GLfloat	m_ambient[4];
	GLfloat	m_diffuse[4];
	GLfloat	m_specular[4];
	GLfloat	m_emission[4];
	GLfloat m_wireframe[4];
	GLfloat	m_shininess;
	GLfloat m_smoothShadeAngle;
	//char	m_textureName[128];
	//CStageTexture *m_texture;
	//GLfloat	m_textureScale;
	//GLint	m_textureAlpha;
	//GLint	m_textureWrap;
	//GLint	m_textureTEV;
	//GLfloat	m_sParameter[4];
	//GLint	m_sMode;
	//GLfloat	m_tParameter[4];
	//GLint	m_tMode;
  
// Operations
	BOOL YoReadPart(FILE *, CStagePart *);
	BOOL YoReadPartFile(char *);
	BOOL YoReadDXFFile(char *);
	BOOL YoGetVertexIndex(GLdouble[3], int *);
	BOOL YoReadPartData(FILE *);
	BOOL YoWritePartFile(FILE *);
	BOOL YoInitPart(CStagePart *);
	BOOL YoMakeDisplayList(GLint);
	BOOL YoComputeNormals(void);
	BOOL YoPositionTexture(GLint, GLint);

	virtual ~CStagePart();
};


class CStageVertexList: public CObject
{
public:
	CStageVertexList()
	{
		int i;
		for (i = 0; i < 20; i++)
		{
			m_polygon[i] = NULL;
		}
		m_next = NULL;
	};
	BOOL YoInsertPolygon(GLint, GLint);
	GLdouble m_vertex[20][3];
	CStagePolygon *m_polygon[20];
	CStageVertexList *m_next;
};

class CStageVertices: public CObject
{
public:
	CStageVertices(){m_next = NULL;};
	GLint m_vertex[4];
	CStageVertices *m_next;
};

class CStageNormals: public CObject
{
public:
	CStageNormals() {m_next = NULL;};
	GLdouble m_normal[4][3];
	CStageNormals *m_next;
};

class CStagePolygonList: public CObject
{
public:
	CStagePolygonList() {m_next = NULL;};
	GLint m_numberSides[10];
	CStageVertices *m_vertices[10];
	GLdouble m_normalFlatShaded[10][3];
	CStageNormals *m_normals[10];
	CStageTexture *m_texture[10];
	CStageTexture *m_origTexture[10];
	BOOL m_textureModified[10];
	GLint m_textureStartVertex[10];
	GLint m_origTextureStartVertex[10];
	CStagePolygonList *m_next;
};

class CStagePolygon: public CObject
{
public:
	CStagePolygon() {m_next = NULL;};
	GLint m_polygon;
	CStagePolygon *m_next;
};

class CStageTexture: public CObject
{
public:
	CStageTexture();
	char m_DIBFileName[128];
	CGLImage *m_RGBImage;
	GLint m_textureMode;
	CStageTextureCoords *m_textureCoords;

// Operations
public:
	//char[128] YoGetDIBFileName() {return m_DIBFileName;};
	BOOL YoInitFromDIB();
	BOOL YoSelectImage(void);
	virtual ~CStageTexture();

};


class CStageTextureCoords: public CObject
{
public:
	CStageTextureCoords() {m_next = NULL;};
	GLdouble m_textureCoords[4][2];
	CStageTextureCoords *m_next;

};




/***
class CStageTexture: public CObject
{
public:
	CStageTexture(CStageDoc *pDoc) {m_pDoc = pDoc;};

	CStageDoc *m_pDoc;
	char m_fileName[128];
	AUX_RGBImageRec* m_pRGBImage;
	GLint m_alpha;
	CStageTexture *m_next;
	CStageTexture *m_nextHash;
	//CTypedPtrList<CObject, CStageTexture*> m_next;
	//CTypedPtrList<CObject, CStageTexture*> m_nextHash;

// Operations

	BOOL YoReadImage(CStagePart *);
	BOOL YoSelectImage(void);
	//const CString GetDIBFileName() 
		//{ return m_DIBFileName;}
   	//BOOL InitFromDIB(const CString, GLint = GL_DECAL);
};
***/

class CStageCommand: public CObject
{
public:
	CStageCommand(CStageDoc *pDoc)
	{
		m_pDoc = pDoc;
		m_next = NULL;
	}

// Attributes
public:
	CStageDoc *m_pDoc;
	SYSTEMTIME m_gmTime;
	double m_time;
	char m_buf[128];
	CStageCommand *m_next;

// Operations
public:
	void YoInsertCommand();
	void YoReadCommands(FILE *);
	void YoWriteCommands(FILE *);

};



class CStageMotion: public CObject
{
public:
	CStageMotion(CStageDoc *pDoc)
	{
		m_pDoc = pDoc;
		m_next = NULL;
	};
protected:
	//DECLARE_SERIAL(CStageMotion)

// Attributes
public:
	CStageDoc *m_pDoc;
	GLint m_time;
	GLint m_type;
	GLdouble m_translate[3];
	GLdouble m_rotate[3];
	CStageMotion *m_next;
	//CTypedPtrList<CObList, CStageMotion*> m_next;

// Operations
public:
	BOOL YoReadMotion(FILE *, class CStagePart *);
	BOOL YoWriteMotion(FILE *, CStagePart *);
};

class CStageEffect: public CObject
{
public:
	CStageEffect(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
//	DECLARE_SERIAL(CStageEffect)

// Attributes
public:
	CStageDoc *m_pDoc;
	GLint m_index;
	GLint m_begin;
	GLint m_end;
	char m_name[64];
	GLint m_priority;
	GLdouble m_props[12];   // maximum effect props
	CStageEffect *m_next;
	//CTypedPtrList<CObList, CStageEffect*> m_next;

// Operations
public:
	BOOL YoReadEffect(FILE *, class CStagePart *ptrPart);
};


class CStageScore: public CObject
{
public:
	CStageScore(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
	//DECLARE_SERIAL(CStageScore)

// Attributes
public:
	CStageDoc *m_pDoc;
	GLint m_time;
	GLdouble m_modelView[16];
	GLfloat	m_ambient[4];
	GLfloat	m_diffuse[4];
	GLfloat	m_specular[4];
	GLfloat	m_emission[4];
	GLfloat m_wireframe[4];
	GLfloat	m_shininess;
	//GLint	m_textureAlpha;
	//GLfloat	m_sParameter[4];
	//GLfloat	m_tParameter[4];
	//struct slnode *layer;
	CStageScore *m_next;
	//CTypedPtrList<CObList, CStageScore*> m_next;

// Operations
};

class CStageEyeScore: public CObject
{
public:
	CStageEyeScore(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
	//DECLARE_SERIAL(CStageEyeScore)

// Attributes
public:
	CStageDoc *m_pDoc;
	GLint m_time;
	GLdouble m_fieldOfView;
	GLdouble m_clipFront;
	GLdouble m_clipRear;
	GLdouble m_eye[9];
	CStageEyeScore *m_next;	

// Operations
};


class CStageEyeMotion: public CObject
{
public:
	CStageEyeMotion(CStageDoc *pDoc) {m_pDoc = pDoc;};
protected:
	//DECLARE_SERIAL(CStageEyeScore)

// Attributes
public:
	CStageDoc *m_pDoc;
	GLint m_time;
	GLint m_type;
	GLdouble m_fieldOfView;
	GLdouble m_clipFront;
	GLdouble m_clipRear;
	GLdouble m_eye[9];
	CStageEyeMotion *m_next;	

// Operations
public:
	BOOL YoReadEyeMotion(FILE *);

};

class CStageEye: public CObject
{
public:
	CStageEye(CStageDoc *pDoc) {m_pDoc = pDoc;};
	void YoCalculateEyePosition(void);
protected:
	//DECLARE_SERIAL(CStageEye)

// Attributes
public:
	CStageDoc *m_pDoc;
	CStageEyeMotion *m_motion;
	//CStageEyeEffect *m_effect;
	CStageEyeScore *m_score;
	CStageEyeScore *m_currentScore;
	BOOL m_moving;
	SYSTEMTIME m_gmTimeStart;
	GLdouble m_timeStart;
	GLdouble m_timeOfMove;
	GLdouble m_fieldOfView[2];
	GLdouble m_clipFront[2];
	GLdouble m_clipRear[2];
	GLdouble m_eye[2][9];
// Operations
};


class CStageEyeView: public CObject
{
public:
	CStageEyeView(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStageEyeView();

// Attributes
public:
	CStageDoc *m_pDoc;
	char m_name[64];
	GLdouble m_eye[12];  // from[3], to[3], up[3], fov, clipFront, clipRear
	CStageEyeView *m_nextHash;

// Operations
	BOOL YoReadEyeView(FILE *);
};	

class CStagePath: public CObject
{
public:
	CStagePath(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStagePath();

// Attributes
public:
	CStageDoc *m_pDoc;
	char m_name[64];
	BOOL m_visible;
	CStagePart *m_ptrPart;
	CStagePath *m_nextHash;
	CStageTag *m_ptrTag;
	CStagePath *m_nextPath;
	GLfloat	m_color[4];

// Operations
public:
	BOOL YoReadPath(FILE *, CStagePart *);
	BOOL YoWritePath(FILE *);
	BOOL YoInitPath(CStagePart *);
	BOOL YoInsertTag(CStageTag *);
	BOOL YoDeleteTag(CStageTag *);
};


class CStageTag: public CObject
{
public:
	CStageTag(CStageDoc *pDoc)
	{
		m_pDoc = pDoc;
		m_prevTag = NULL;
		m_nextTag = NULL;
		m_pick = NULL;
		m_displayListID = 0;
	};

	~CStageTag();
protected:
	//DECLARE_SERIAL(CStageTag)

// Attributes
public:
	CStageDoc *m_pDoc;
	UINT m_tag;
	GLint m_displayListID;
	CStageTag *m_prevTag;
	CStageTag *m_nextTag;
	CStagePath *m_ptrPath;
	GLdouble m_translate[3];
	GLdouble m_rotate[3];
	CStageTag *m_pick;


// Operations

};



class CStageSocket:public CAsyncSocket
{
public:
	CStageSocket(CStageDoc *pDoc) {m_pDoc = pDoc;};
	~CStageSocket() 
	{
		if (this == m_pDoc->m_acceptSocket)
		{
			m_pDoc->m_acceptSocket = NULL;
		}
		else if (this == m_pDoc->m_socket)
		{
			m_pDoc->m_socket = NULL;
		}
	};
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CStageDoc *m_pDoc;
	char m_buf[4096];
};

/***
class CStageThreadPlay:public CObject
{
public:
	HWND m_hframeWND;
	HWND m_hviewWND;
	HDC m_hdocDC;
};
***/

class CStageUndo: public CObject
{
public:
	CStageUndo(CStageDoc *pDoc) 
	{
		m_pDoc = pDoc;
		m_undoMode = YO_UNDO_OFF;
		m_undoDeviceDelete = NULL;
		m_undoPartDelete = NULL;
		m_undoTagDelete = NULL;
	};
	//~CStageUndo();

// Attributes
public:
	CStageDoc *m_pDoc;
	int m_undoMode;
	double m_undoEye[9];
	double m_undoPartTranslate[3];
	CStageDevice *m_undoDeviceDelete;
	CStagePart *m_undoPartDelete;
	CStageTag *m_undoTagDelete;

// Operations
public:
	void YoUndo(void);
};
