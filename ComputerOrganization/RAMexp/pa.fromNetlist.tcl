
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name Sram_Write_Read -dir "D:/CO exps/4/Sram_Write_Read/planAhead_run_1" -part xc3s1200efg320-4
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "D:/CO exps/4/Sram_Write_Read/Sram_Write_Read.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {D:/CO exps/4/Sram_Write_Read} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "D:/CO exps/ucfs/Sram_Write_Read.ucf" [current_fileset -constrset]
add_files [list {D:/CO exps/ucfs/Sram_Write_Read.ucf}] -fileset [get_property constrset [current_run]]
link_design
