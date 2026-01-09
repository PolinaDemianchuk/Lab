package com.rest.crud;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/tasks")
public class Controller
{
    private final TaskRepository taskRep;

    public Controller(TaskRepository taskRep)
    {
        this.taskRep = taskRep;
    }

    @GetMapping
    public List<Task> getAllTasks()
    {
        return taskRep.findAll();
    }

    @PostMapping
    public ResponseEntity<Task> createTask(@RequestBody Task task)
    {
        if (task.getStatus() == null)
        {
            task.setStatus("todo");
        }
        Task saveTask = taskRep.save(task);
        return new ResponseEntity<>(saveTask, HttpStatus.CREATED);
    }

    @GetMapping("/{id}")
    public ResponseEntity<Task> getTaskById(@PathVariable Long id)
    {
        return taskRep.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PutMapping("/{id}")
    public ResponseEntity<Task> updateTask(@PathVariable Long id, @RequestBody Task taskDetails)
    {
        return taskRep.findById(id).map(task ->
        {
            task.setTitle(taskDetails.getTitle());
            task.setDescription(taskDetails.getDescription());
            task.setStatus(taskDetails.getStatus());
            return ResponseEntity.ok(taskRep.save(task));
        }).orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteTask(@PathVariable Long id)
    {
        if (taskRep.existsById(id))
        {
            taskRep.deleteById(id);
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.notFound().build();
    }

}