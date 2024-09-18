MWS Result File Version 20150206
size=i:105

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:solverstart
result=s:1
files=s:Beam_starter_losses.slim

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:solverstart
result=s:1
files=s:Beam_starter.pwr

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:solverstart
result=s:1
files=s:thermallosses.tlz

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:ParticleSurfaceLosses_Beam_starter.gex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:ParticleSurfaceLosses_Beam_starter.slim

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:ParticleSurfaceLosses_Beam_starter.sct

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:trajectories.bix

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_0_0_sh_current.m3d

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_0_0_se_charge.m3d

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_eldens_m3d.rex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_eldens.ffn

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_d_m3d.rex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_d.ffn

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_e_m3d.rex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_e.ffn

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:field_se_phi_m3d.rex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:solverstart
result=s:0
files=s:PBAMeshFeedback.axg

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
files=s:World.fid

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:survivemeshadapt
result=s:1
files=s:model.gex

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:survivemeshadapt
result=s:1
files=s:PP.sid

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:survivemeshadapt
result=s:1
files=s:PP.fmm

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:solverstart
result=s:0
files=s:Beam_starter.ipd

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
files=s:simulation_overview.json

type=s:HIDDENITEM
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:persistent
result=s:0
files=s:MCalcAccess.log

type=s:FOLDER
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:persistent
result=s:0
treepath=s:1D Results

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Initial Timestep
files=s:InitialTimestep.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Mesh Step\Smallest
files=s:MeshStep_Smallest.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Mesh Step\Largest
files=s:MeshStep_Largest.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Mesh Step\Characteristic
files=s:MeshStep_Characteristic.0d

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Convergence\Electrostatic Solver\Residual
files=s:Electrostatic Solver_Residual.sig

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Accuracy
files=s:EsSolver_Accuracy.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Energy
files=s:EsSolver_Energy.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Charges\Coil
files=s:EsSolver_Charges_Coil.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Charges\Folder1:Wehnelt
files=s:EsSolver_Charges_Folder1_Wehnelt.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Charges\Grid
files=s:EsSolver_Charges_Grid.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Es Solver\Charges\Platte
files=s:EsSolver_Charges_Platte.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Particle Sources\Virtual Gap Distance\Beam_starter
files=s:ParticleSources_VirtualGapDistance_Beam_starter.0d

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Particle Sources\Charge vs. Iteration\Beam_starter
files=s:Beam_starter_charge.sig

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Particle Sources\Current vs. Iteration\Beam_starter
files=s:Beam_starter_current.sig

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Particle Sources\Perveance vs. Iteration\Beam_starter
files=s:Beam_starter_perveance.sig

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\[Background]: Boundary
files=s:TotalCollisionInformation_Current_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\[Background]: Boundary
files=s:TotalCollisionInformation_Power_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\[Background]: Boundary
files=s:TotalCollisionInformation_Particles_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\component1: Spule
files=s:TotalCollisionInformation_Current_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\component1: Spule
files=s:TotalCollisionInformation_Power_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\component1: Spule
files=s:TotalCollisionInformation_Particles_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\default: Glass
files=s:TotalCollisionInformation_Current_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\default: Glass
files=s:TotalCollisionInformation_Power_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\default: Glass
files=s:TotalCollisionInformation_Particles_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\default: WehneltCylinder
files=s:TotalCollisionInformation_Current_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\default: WehneltCylinder
files=s:TotalCollisionInformation_Power_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\default: WehneltCylinder
files=s:TotalCollisionInformation_Particles_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\default: import_2
files=s:TotalCollisionInformation_Current_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\default: import_2
files=s:TotalCollisionInformation_Power_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\default: import_2
files=s:TotalCollisionInformation_Particles_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Current\default: import_3
files=s:TotalCollisionInformation_Current_default_import_3.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Power\default: import_3
files=s:TotalCollisionInformation_Power_default_import_3.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\Total Collision Information\Particles\default: import_3
files=s:TotalCollisionInformation_Particles_default_import_3.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:surviveparchange
result=s:1
parametric=s:P
treepath=s:1D Results\AutomaticRunInformation
files=s:AutomaticRunInformation

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::11:8
visibility=s:visible
creation=s:internal
lifetime=s:persistent
result=s:0
treepath=s:Excitation Signals\default
files=s:signal_default_lf.sig

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Initial Timestep
files=s:InitialTimestep.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Mesh Step\Smallest
files=s:MeshStep_Smallest.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Mesh Step\Largest
files=s:MeshStep_Largest.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Mesh Step\Characteristic
files=s:MeshStep_Characteristic.0d

type=s:MESH_FEEDBACK
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:solverstart
result=s:0
treepath=s:Mesh\Information\PBA
files=s:PBAMeshFeedback.rex
ylabel=s:Mesh Feedback

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Convergence\Electrostatic Solver\Residual
files=s:Electrostatic Solver_Residual.sig

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Accuracy
files=s:EsSolver_Accuracy.0d

type=s:POTENTIAL
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\Potential [Es]
files=s:field_se_phi.m3d
files=s:field_se_phi_m3d.rex

type=s:EFIELD3D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\E-Field [Es]
files=s:field_se_e.m3d
files=s:field_se_e_m3d.rex

type=s:DFIELD3D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\D-Field [Es]
files=s:field_se_d.m3d
files=s:field_se_d_m3d.rex

type=s:EENERGY3D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\El. Energy Dens. [Es]
files=s:field_se_eldens.m3d
files=s:field_se_eldens_m3d.rex

type=s:SOLVERTEXTFILE
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:Electric Field Energy
files=s:Electric Field Energy.stx

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Energy
files=s:EsSolver_Energy.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Charges\Coil
files=s:EsSolver_Charges_Coil.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Charges\Folder1:Wehnelt
files=s:EsSolver_Charges_Folder1_Wehnelt.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Charges\Grid
files=s:EsSolver_Charges_Grid.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Es Solver\Charges\Platte
files=s:EsSolver_Charges_Platte.0d

type=s:SOLVERTEXTFILE
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:Charge Values
files=s:Charge Values.stx

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Particle Sources\Virtual Gap Distance\Beam_starter
files=s:ParticleSources_VirtualGapDistance_Beam_starter.0d

type=s:CHARGE
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\Particle Charge Density
files=s:field_0_0_se_charge_m3d.rex

type=s:EXCICURRENT3D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\Particle Current Density
files=s:field_0_0_sh_current_m3d.rex

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Particle Sources\Charge vs. Iteration\Beam_starter
files=s:Beam_starter_charge.sig

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Particle Sources\Current vs. Iteration\Beam_starter
files=s:Beam_starter_current.sig

type=s:XYSIGNAL2
subtype=s:user
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Particle Sources\Perveance vs. Iteration\Beam_starter
files=s:Beam_starter_perveance.sig

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\[Background]: Boundary
files=s:TotalCollisionInformation_Current_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\[Background]: Boundary
files=s:TotalCollisionInformation_Power_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\[Background]: Boundary
files=s:TotalCollisionInformation_Particles_[Background]_Boundary.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\component1: Spule
files=s:TotalCollisionInformation_Current_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\component1: Spule
files=s:TotalCollisionInformation_Power_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\component1: Spule
files=s:TotalCollisionInformation_Particles_component1_Spule.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\default: Glass
files=s:TotalCollisionInformation_Current_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\default: Glass
files=s:TotalCollisionInformation_Power_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\default: Glass
files=s:TotalCollisionInformation_Particles_default_Glass.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\default: WehneltCylinder
files=s:TotalCollisionInformation_Current_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\default: WehneltCylinder
files=s:TotalCollisionInformation_Power_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\default: WehneltCylinder
files=s:TotalCollisionInformation_Particles_default_WehneltCylinder.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\default: import_2
files=s:TotalCollisionInformation_Current_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\default: import_2
files=s:TotalCollisionInformation_Power_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\default: import_2
files=s:TotalCollisionInformation_Particles_default_import_2.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Current\default: import_3
files=s:TotalCollisionInformation_Current_default_import_3.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Power\default: import_3
files=s:TotalCollisionInformation_Power_default_import_3.0d

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\Total Collision Information\Particles\default: import_3
files=s:TotalCollisionInformation_Particles_default_import_3.0d

type=s:PARTICLEPOS3D
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\Trajectories
files=s:trajectories_bix.rex

type=s:SURFACEPWRLOSS_TET
problemclass=s::8:1000
visibility=s:visible
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:2D/3D Results\Particle Surface Collision Losses\Beam_starter
files=s:ParticleSurfaceLosses_Beam_starter.rex
ylabel=s:Particle Collision Surface Losses - Beam_starter

type=s:RESULT_0D
problemclass=s::8:1000
visibility=s:hidden
creation=s:internal
lifetime=s:rebuild
result=s:1
treepath=s:1D Results\AutomaticRunInformation
files=s:AutomaticRunInformation

