extends Node2D



func _process(delta):
	on_enter_to_change_scene()

func on_enter_to_change_scene():
	if Input.is_action_just_pressed("ui_accept"):
		get_tree().change_scene_to_file("res://world.tscn")

func _on_btn_play_pressed():
	get_tree().change_scene_to_file("res://world.tscn")
	


func _on_btn_quit_pressed():
	get_tree().quit()
