<?xml version="1.0" encoding="UTF-8"?>
<MetaResultFile version="20211011" creator="Solver_TRK">
  <MetaGeometryFile filename="model.gex" lod="1"/>
  <SimulationProperties fieldname="Particle Current Density" frequency="0" encoded_unit="&amp;U:A^1.:m^-2" fieldtype="Particle Current Density" fieldscaling="UNDEFINED" dB_Amplitude="20"/>
  <ResultDataType vector="1" complex="0" timedomain="0" frequencymap="0"/>
  <SimulationDomain min="0 0 0" max="0 0 0"/>
  <PlotSettings Plot="4" ignore_symmetry="0" deformation="0" enforce_culling="0" integer_values="0" combine="CombineNone" default_arrow_type="ARROWS" default_scaling="NONE"/>
  <Source type="SOLVER"/>
  <SpecialMaterials>
    <Background type="NORMAL"/>
    <Material name="Aluminum" type="FIELDFREE"/>
    <Material name="PEC" type="FIELDFREE"/>
    <Material name="default" type="FIELDFREE"/>
  </SpecialMaterials>
  <AuxGeometryFile/>
  <AuxResultFile/>
  <FieldFreeNodes/>
  <SurfaceFieldCoefficients/>
  <UnitCell/>
  <SubVolume/>
  <Units/>
  <ProjectUnits/>
  <TimeSampling/>
  <LocalAxes/>
  <MeshViewSettings/>
  <ResultGroups num_steps="1" transformation="1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1" process_mesh_group="0">
    <SharedDataWith/>
    <Frame index="0" characteristic="0">
      <FieldResultFile filename="field_0_0_sh_current.m3d" type="m3d"/>
    </Frame>
  </ResultGroups>
</MetaResultFile>
