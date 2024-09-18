<?xml version="1.0" encoding="UTF-8"?>
<MetaResultFile version="20140508" creator="ParticleSolver">
  <MetaGeometryFile filename="model.gex" lod="1"/>
  <SimulationProperties fieldname="Trajectories" frequency="0" encoded_unit="&amp;U" fieldscaling="UNDEFINED"/>
  <ResultDataType vector="0" complex="0" timedomain="1" frequencymap="0"/>
  <SimulationDomain min="0 0 0" max="0 0 0"/>
  <PlotSettings Plot="128" ignore_symmetry="0" deformation="0" enforce_culling="0" integer_values="0" combine="CombineNone" default_arrow_type="ARROWS" default_scaling="NONE"/>
  <Source type="SOLVER"/>
  <SpecialMaterials>
    <Background type="NORMAL"/>
  </SpecialMaterials>
  <AuxGeometryFile/>
  <AuxResultFile/>
  <FieldFreeNodes/>
  <SurfaceFieldCoefficients/>
  <UnitCell/>
  <SubVolume/>
  <Units/>
  <ProjectUnits>
    <Quantity name="length" unit="&amp;Um:m^1"/>
    <Quantity name="frequency" unit="&amp;UG:Hz^1"/>
    <Quantity name="time" unit="&amp;Un:s^1"/>
    <Quantity name="temperature" unit="&amp;U:Cel^1"/>
  </ProjectUnits>
  <TimeSampling start="-0.00013205540017224848" end="25.65723991394043" step="0.25657370686531067"/>
  <LocalAxes/>
  <MeshViewSettings/>
  <ResultGroups num_steps="1" transformation="1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1" process_mesh_group="0">
    <SharedDataWith/>
    <Frame index="0" characteristic="0">
      <FieldResultFile filename="trajectories.bix" type="bix"/>
    </Frame>
  </ResultGroups>
  <ParticleSrcToId>
    <Item name="Beam_starter" id="0"/>
  </ParticleSrcToId>
  <Quantities>
    <Quantity field="Momentum" plot="Energy" encoded_unit="&amp;U:eV^1" quantity="energy"/>
    <Quantity field="Momentum" plot="Normed Momentum" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
    <Quantity field="Momentum" plot="Gamma" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
    <Quantity field="Momentum" plot="Beta" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
    <Quantity field="Momentum" plot="Velocity" encoded_unit="&amp;U:m^1.:s^-1" quantity="velocity"/>
    <Quantity field="ChargeMacro" plot="Macro Charge" encoded_unit="&amp;U:C^1" quantity="charge"/>
    <Quantity field="ParticleID" plot="Trajectory ID" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
    <Quantity field="EmissionID" plot="Particle Source" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
    <Quantity field="Time" plot="Time of flight" encoded_unit="&amp;Un:s^1" quantity="time"/>
    <Quantity field="SEEGeneration" plot="SEE Generation" encoded_unit="&amp;U:1^1" quantity="dimensionless"/>
  </Quantities>
  <Extrema sample="TimeGlobal">
    <Min name="Energy" value="0" position="0 0 0"/>
    <Min name="Normed Momentum" value="9.323681382511495e-09" position="0 0 0"/>
    <Min name="Gamma" value="1" position="0 0 0"/>
    <Min name="Beta" value="9.323681382511495e-09" position="0 0 0"/>
    <Min name="Velocity" value="2.7951693534851074" position="0 0 0"/>
    <Min name="Macro Charge" value="-1.9225194795168515e-19" position="0 0 0"/>
    <Min name="Trajectory ID" value="0" position="0 0 0"/>
    <Min name="Particle Source" value="0" position="0 0 0"/>
    <Min name="Time of flight" value="-0.00013205540017224848" position="0 0 0"/>
    <Min name="SEE Generation" value="0" position="0 0 0"/>
    <Max name="Energy" value="1264.39501953125" position="0 0 0"/>
    <Max name="Normed Momentum" value="0.07039063423871994" position="0 0 0"/>
    <Max name="Gamma" value="1.002474308013916" position="0 0 0"/>
    <Max name="Beta" value="0.070216894149780273" position="0 0 0"/>
    <Max name="Velocity" value="21050494" position="0 0 0"/>
    <Max name="Macro Charge" value="-5.4586754430081041e-32" position="0 0 0"/>
    <Max name="Trajectory ID" value="53927" position="0 0 0"/>
    <Max name="Particle Source" value="0" position="0 0 0"/>
    <Max name="Time of flight" value="25.65723991394043" position="0 0 0"/>
    <Max name="SEE Generation" value="0" position="0 0 0"/>
  </Extrema>
</MetaResultFile>
