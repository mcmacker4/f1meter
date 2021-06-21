#ifndef F1METER_PACKETTYPES_H
#define F1METER_PACKETTYPES_H

#include <cstdint>
#include <algorithm>

namespace F1Raw {

    enum PacketId {
        MOTION = 0,
        SESSION,
        LAP_DATA,
        EVENT,
        PARTICIPANTS,
        CAR_SETUPS,
        CAR_TELEMETRY,
        CAR_STATUS,
        FINAL_CLASSIFICATION,
        LOBBY_INFO,
    };

#pragma pack(push, 1)
    struct PacketHeader {
        uint16_t packetFormat;             // 2020
        uint8_t gameMajorVersion;         // Game major version - "X.00"
        uint8_t gameMinorVersion;         // Game minor version - "1.XX"
        uint8_t packetVersion;            // Version of this packet type, all start from 1
        uint8_t packetId;                 // Identifier for the packet type, see below
        uint64_t sessionUID;               // Unique identifier for the session
        float sessionTime;              // Session timestamp
        uint32_t frameIdentifier;          // Identifier for the frame the data was retrieved on
        uint8_t playerCarIndex;           // Index of player's car in the array

        // ADDED IN BETA 2:
        uint8_t secondaryPlayerCarIndex;  // Index of secondary player's car in the array (splitscreen)
        // 255 if no second player
    };

    struct CarMotionData {
        float worldPositionX;           // World space X position
        float worldPositionY;           // World space Y position
        float worldPositionZ;           // World space Z position
        float worldVelocityX;           // Velocity in world space X
        float worldVelocityY;           // Velocity in world space Y
        float worldVelocityZ;           // Velocity in world space Z
        int16_t worldForwardDirX;         // World space forward X direction (normalised)
        int16_t worldForwardDirY;         // World space forward Y direction (normalised)
        int16_t worldForwardDirZ;         // World space forward Z direction (normalised)
        int16_t worldRightDirX;           // World space right X direction (normalised)
        int16_t worldRightDirY;           // World space right Y direction (normalised)
        int16_t worldRightDirZ;           // World space right Z direction (normalised)
        float gForceLateral;            // Lateral G-Force component
        float gForceLongitudinal;       // Longitudinal G-Force component
        float gForceVertical;           // Vertical G-Force component
        float yaw;                      // Yaw angle in radians
        float pitch;                    // Pitch angle in radians
        float roll;                     // Roll angle in radians
    };

    struct PacketMotionData {
        PacketHeader header;                // Header

        CarMotionData carMotionData[22];        // Data for all cars on track

        // Extra player car ONLY data
        float suspensionPosition[4];      // Note: All wheel arrays have the following order:
        float suspensionVelocity[4];      // RL, RR, FL, FR
        float suspensionAcceleration[4];    // RL, RR, FL, FR
        float wheelSpeed[4];            // Speed of each wheel
        float wheelSlip[4];               // Slip ratio for each wheel
        float localVelocityX;            // Velocity in local space
        float localVelocityY;            // Velocity in local space
        float localVelocityZ;            // Velocity in local space
        float angularVelocityX;            // Angular velocity x-component
        float angularVelocityY;           // Angular velocity y-component
        float angularVelocityZ;           // Angular velocity z-component
        float angularAccelerationX;       // Angular velocity x-component
        float angularAccelerationY;        // Angular velocity y-component
        float angularAccelerationZ;       // Angular velocity z-component
        float frontWheelsAngle;           // Current front wheels angle in radians
    };

    struct MarshalZone {
        float zoneStart;   // Fraction (0..1) of way through the lap the marshal zone starts
        int8_t zoneFlag;    // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
    };

    struct WeatherForecastSample {
        uint8_t sessionType;                     // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
        // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
        // 12 = Time Trial
        uint8_t timeOffset;                      // Time in minutes the forecast is for
        uint8_t weather;                         // Weather - 0 = clear, 1 = light cloud, 2 = overcast
        // 3 = light rain, 4 = heavy rain, 5 = storm
        int8_t trackTemperature;                // Track temp. in degrees celsius
        int8_t airTemperature;                  // Air temp. in degrees celsius
    };

    struct PacketSessionData {
        PacketHeader header;                    // Header

        uint8_t weather;                   // Weather - 0 = clear, 1 = light cloud, 2 = overcast
        // 3 = light rain, 4 = heavy rain, 5 = storm
        int8_t trackTemperature;          // Track temp. in degrees celsius
        int8_t airTemperature;            // Air temp. in degrees celsius
        uint8_t totalLaps;                 // Total number of laps in this race
        uint16_t trackLength;               // Track length in metres
        uint8_t sessionType;               // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
        // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
        // 10 = R, 11 = R2, 12 = Time Trial
        int8_t trackId;                   // -1 for unknown, 0-21 for tracks, see appendix
        uint8_t formula;                   // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
        // 3 = F1 Generic
        uint16_t sessionTimeLeft;           // Time left in session in seconds
        uint16_t sessionDuration;           // Session duration in seconds
        uint8_t pitSpeedLimit;             // Pit speed limit in kilometres per hour
        uint8_t gamePaused;                // Whether the game is paused
        uint8_t isSpectating;              // Whether the player is spectating
        uint8_t spectatorCarIndex;         // Index of the car being spectated
        uint8_t sliProNativeSupport;     // SLI Pro support, 0 = inactive, 1 = active
        uint8_t numMarshalZones;           // Number of marshal zones to follow
        MarshalZone marshalZones[21];          // List of marshal zones – max 21
        uint8_t safetyCarStatus;           // 0 = no safety car, 1 = full safety car
        // 2 = virtual safety car
        uint8_t networkGame;               // 0 = offline, 1 = online
        uint8_t numWeatherForecastSamples; // Number of weather samples to follow
        WeatherForecastSample weatherForecastSamples[20];   // Array of weather forecast samples
    };

    struct LapData {
        float lastLapTime;               // Last lap time in seconds
        float currentLapTime;            // Current time around the lap in seconds

        //UPDATED in Beta 3:
        uint16_t sector1TimeInMS;           // Sector 1 time in milliseconds
        uint16_t sector2TimeInMS;           // Sector 2 time in milliseconds
        float bestLapTime;               // Best lap time of the session in seconds
        uint8_t bestLapNum;                // Lap number best time achieved on
        uint16_t bestLapSector1TimeInMS;    // Sector 1 time of best lap in the session in milliseconds
        uint16_t bestLapSector2TimeInMS;    // Sector 2 time of best lap in the session in milliseconds
        uint16_t bestLapSector3TimeInMS;    // Sector 3 time of best lap in the session in milliseconds
        uint16_t bestOverallSector1TimeInMS;// Best overall sector 1 time of the session in milliseconds
        uint8_t bestOverallSector1LapNum;  // Lap number best overall sector 1 time achieved on
        uint16_t bestOverallSector2TimeInMS;// Best overall sector 2 time of the session in milliseconds
        uint8_t bestOverallSector2LapNum;  // Lap number best overall sector 2 time achieved on
        uint16_t bestOverallSector3TimeInMS;// Best overall sector 3 time of the session in milliseconds
        uint8_t bestOverallSector3LapNum;  // Lap number best overall sector 3 time achieved on


        float lapDistance;               // Distance vehicle is around current lap in metres – could
        // be negative if line hasn’t been crossed yet
        float totalDistance;             // Total distance travelled in session in metres – could
        // be negative if line hasn’t been crossed yet
        float safetyCarDelta;            // Delta in seconds for safety car
        uint8_t carPosition;               // Car race position
        uint8_t currentLapNum;             // Current lap number
        uint8_t pitStatus;                 // 0 = none, 1 = pitting, 2 = in pit area
        uint8_t sector;                    // 0 = sector1, 1 = sector2, 2 = sector3
        uint8_t currentLapInvalid;         // Current lap invalid - 0 = valid, 1 = invalid
        uint8_t penalties;                 // Accumulated time penalties in seconds to be added
        uint8_t gridPosition;              // Grid position the vehicle started the race in
        uint8_t driverStatus;              // Status of driver - 0 = in garage, 1 = flying lap
        // 2 = in lap, 3 = out lap, 4 = on track
        uint8_t resultStatus;              // Result status - 0 = invalid, 1 = inactive, 2 = active
        // 3 = finished, 4 = disqualified, 5 = not classified
        // 6 = retired
    };


    struct PacketLapData {
        PacketHeader header;             // Header

        LapData lapData[22];        // Lap data for all cars on track
    };

// The event details packet is different for each type of event.
// Make sure only the correct type is interpreted.
    union EventDataDetails {
        struct {
            uint8_t vehicleIdx; // Vehicle index of car achieving fastest lap
            float lapTime;    // Lap time is in seconds
        } FastestLap;

        struct {
            uint8_t vehicleIdx; // Vehicle index of car retiring
        } Retirement;

        struct {
            uint8_t vehicleIdx; // Vehicle index of team mate
        } TeamMateInPits;

        struct {
            uint8_t vehicleIdx; // Vehicle index of the race winner
        } RaceWinner;

        struct {
            uint8_t penaltyType;          // Penalty type – see Appendices
            uint8_t infringementType;     // Infringement type – see Appendices
            uint8_t vehicleIdx;           // Vehicle index of the car the penalty is applied to
            uint8_t otherVehicleIdx;      // Vehicle index of the other car involved
            uint8_t time;                 // Time gained, or time spent doing action in seconds
            uint8_t lapNum;               // Lap the penalty occurred on
            uint8_t placesGained;         // Number of places gained by this
        } Penalty;

        struct {
            uint8_t vehicleIdx; // Vehicle index of the vehicle triggering speed trap
            float speed;      // Top speed achieved in kilometres per hour
        } SpeedTrap;
    };

    struct PacketEventData {
        PacketHeader header;             // Header

        uint8_t eventStringCode[4]; // Event string code, see below
        EventDataDetails eventDetails;       // Event details - should be interpreted differently
        // for each type
    };

    struct ParticipantData {
        uint8_t aiControlled;           // Whether the vehicle is AI (1) or Human (0) controlled
        uint8_t driverId;               // Driver id - see appendix
        uint8_t teamId;                 // Team id - see appendix
        uint8_t raceNumber;             // Race number of the car
        uint8_t nationality;            // Nationality of the driver
        char name[48];               // Name of participant in UTF-8 format – null terminated
        // Will be truncated with … (U+2026) if too long
        uint8_t yourTelemetry;          // The player's UDP setting, 0 = restricted, 1 = public
    };

    struct PacketParticipantsData {
        PacketHeader header;           // Header

        uint8_t numActiveCars;    // Number of active cars in the data – should match number of
        // cars on HUD
        ParticipantData participants[22];
    };

    struct CarSetupData {
        uint8_t frontWing;                // Front wing aero
        uint8_t rearWing;                 // Rear wing aero
        uint8_t onThrottle;               // Differential adjustment on throttle (percentage)
        uint8_t offThrottle;              // Differential adjustment off throttle (percentage)
        float frontCamber;              // Front camber angle (suspension geometry)
        float rearCamber;               // Rear camber angle (suspension geometry)
        float frontToe;                 // Front toe angle (suspension geometry)
        float rearToe;                  // Rear toe angle (suspension geometry)
        uint8_t frontSuspension;          // Front suspension
        uint8_t rearSuspension;           // Rear suspension
        uint8_t frontAntiRollBar;         // Front anti-roll bar
        uint8_t rearAntiRollBar;          // Front anti-roll bar
        uint8_t frontSuspensionHeight;    // Front ride height
        uint8_t rearSuspensionHeight;     // Rear ride height
        uint8_t brakePressure;            // Brake pressure (percentage)
        uint8_t brakeBias;                // Brake bias (percentage)
        float rearLeftTyrePressure;     // Rear left tyre pressure (PSI)
        float rearRightTyrePressure;    // Rear right tyre pressure (PSI)
        float frontLeftTyrePressure;    // Front left tyre pressure (PSI)
        float frontRightTyrePressure;   // Front right tyre pressure (PSI)
        uint8_t ballast;                  // Ballast
        float fuelLoad;                 // Fuel load
    };

    struct PacketCarSetupData {
        PacketHeader header;            // Header

        CarSetupData carSetups[22];
    };

    struct CarTelemetryData {
        uint16_t speed;                         // Speed of car in kilometres per hour
        float throttle;                      // Amount of throttle applied (0.0 to 1.0)
        float steer;                         // Steering (-1.0 (full lock left) to 1.0 (full lock right))
        float brake;                         // Amount of brake applied (0.0 to 1.0)
        uint8_t clutch;                        // Amount of clutch applied (0 to 100)
        int8_t gear;                          // Gear selected (1-8, N=0, R=-1)
        uint16_t engineRPM;                     // Engine RPM
        uint8_t drs;                           // 0 = off, 1 = on
        uint8_t revLightsPercent;              // Rev lights indicator (percentage)
        uint16_t brakesTemperature[4];          // Brakes temperature (celsius)
        uint8_t tyresSurfaceTemperature[4];    // Tyres surface temperature (celsius)
        uint8_t tyresInnerTemperature[4];      // Tyres inner temperature (celsius)
        uint16_t engineTemperature;             // Engine temperature (celsius)
        float tyresPressure[4];              // Tyres pressure (PSI)
        uint8_t surfaceType[4];                // Driving surface, see appendices
    };

    struct PacketCarTelemetryData {
        PacketHeader header;           // Header

        CarTelemetryData carTelemetryData[22];

        uint32_t buttonStatus;        // Bit flags specifying which buttons are being pressed
        // currently - see appendices

        // Added in Beta 3:
        uint8_t mfdPanelIndex;       // Index of MFD panel open - 255 = MFD closed
        // Single player, race – 0 = Car setup, 1 = Pits
        // 2 = Damage, 3 =  Engine, 4 = Temperatures
        // May vary depending on game mode
        uint8_t mfdPanelIndexSecondaryPlayer;   // See above
        int8_t suggestedGear;       // Suggested gear for the player (1-8)
        // 0 if no gear suggested
    };

    struct CarStatusData {
        uint8_t tractionControl;          // 0 (off) - 2 (high)
        uint8_t antiLockBrakes;           // 0 (off) - 1 (on)
        uint8_t fuelMix;                  // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
        uint8_t frontBrakeBias;           // Front brake bias (percentage)
        uint8_t pitLimiterStatus;         // Pit limiter status - 0 = off, 1 = on
        float fuelInTank;               // Current fuel mass
        float fuelCapacity;             // Fuel capacity
        float fuelRemainingLaps;        // Fuel remaining in terms of laps (value on MFD)
        uint16_t maxRPM;                   // Cars max RPM, point of rev limiter
        uint16_t idleRPM;                  // Cars idle RPM
        uint8_t maxGears;                 // Maximum number of gears
        uint8_t drsAllowed;               // 0 = not allowed, 1 = allowed, -1 = unknown


        // Added in Beta3:
        uint16_t drsActivationDistance;    // 0 = DRS not available, non-zero - DRS will be available
        // in [X] metres

        uint8_t tyresWear[4];             // Tyre wear percentage
        uint8_t actualTyreCompound;        // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
        // 7 = inter, 8 = wet
        // F1 Classic - 9 = dry, 10 = wet
        // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
        // 15 = wet
        uint8_t visualTyreCompound;        // F1 visual (can be different from actual compound)
        // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
        // F1 Classic – same as above
        // F2 – same as above
        uint8_t tyresAgeLaps;             // Age in laps of the current set of tyres
        uint8_t tyresDamage[4];           // Tyre damage (percentage)
        uint8_t frontLeftWingDamage;      // Front left wing damage (percentage)
        uint8_t frontRightWingDamage;     // Front right wing damage (percentage)
        uint8_t rearWingDamage;           // Rear wing damage (percentage)

        // Added Beta 3:
        uint8_t drsFault;                 // Indicator for DRS fault, 0 = OK, 1 = fault

        uint8_t engineDamage;             // Engine damage (percentage)
        uint8_t gearBoxDamage;            // Gear box damage (percentage)
        int8_t vehicleFiaFlags;          // -1 = invalid/unknown, 0 = none, 1 = green
        // 2 = blue, 3 = yellow, 4 = red
        float ersStoreEnergy;           // ERS energy store in Joules
        uint8_t ersDeployMode;            // ERS deployment mode, 0 = none, 1 = medium
        // 2 = overtake, 3 = hotlap
        float ersHarvestedThisLapMGUK;  // ERS energy harvested this lap by MGU-K
        float ersHarvestedThisLapMGUH;  // ERS energy harvested this lap by MGU-H
        float ersDeployedThisLap;       // ERS energy deployed this lap
    };

    struct PacketCarStatusData {
        PacketHeader header;           // Header

        CarStatusData carStatusData[22];
    };

    struct FinalClassificationData {
        uint8_t position;              // Finishing position
        uint8_t numLaps;               // Number of laps completed
        uint8_t gridPosition;          // Grid position of the car
        uint8_t points;                // Number of points scored
        uint8_t numPitStops;           // Number of pit stops made
        uint8_t resultStatus;          // Result status - 0 = invalid, 1 = inactive, 2 = active
        // 3 = finished, 4 = disqualified, 5 = not classified
        // 6 = retired
        float bestLapTime;           // Best lap time of the session in seconds
        double totalRaceTime;         // Total race time in seconds without penalties
        uint8_t penaltiesTime;         // Total penalties accumulated in seconds
        uint8_t numPenalties;          // Number of penalties applied to this driver
        uint8_t numTyreStints;         // Number of tyres stints up to maximum
        uint8_t tyreStintsActual[8];   // Actual tyres used by this driver
        uint8_t tyreStintsVisual[8];   // Visual tyres used by this driver
    };

    struct PacketFinalClassificationData {
        PacketHeader header;                             // Header

        uint8_t numCars;                 // Number of cars in the final classification
        FinalClassificationData classificationData[22];
    };

    struct LobbyInfoData {
        uint8_t aiControlled;            // Whether the vehicle is AI (1) or Human (0) controlled
        uint8_t teamId;                  // Team id - see appendix (255 if no team currently selected)
        uint8_t nationality;             // Nationality of the driver
        char name[48];                // Name of participant in UTF-8 format – null terminated
        // Will be truncated with ... (U+2026) if too long
        uint8_t readyStatus;             // 0 = not ready, 1 = ready, 2 = spectating
    };

    struct PacketLobbyInfoData {
        PacketHeader header;                       // Header

        // Packet specific data
        uint8_t numPlayers;               // Number of players in the lobby data
        LobbyInfoData lobbyPlayers[22];
    };

#pragma pack(pop)

    static const size_t MAX_PACKET_SIZE = std::max({
                                                           sizeof(PacketMotionData),
                                                           sizeof(PacketSessionData),
                                                           sizeof(PacketLapData),
                                                           sizeof(PacketEventData),
                                                           sizeof(PacketParticipantsData),
                                                           sizeof(PacketCarSetupData),
                                                           sizeof(PacketCarTelemetryData),
                                                           sizeof(PacketCarStatusData),
                                                           sizeof(PacketFinalClassificationData),
                                                           sizeof(PacketLobbyInfoData)
                                                   });

}

#endif //F1METER_PACKETTYPES_H
