package com.rest.crud;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.List;

@RestController
@RequestMapping("/tasks")
public class Controller
{
    @Autowired
    private Message msg;

    private static final Logger log = LoggerFactory.getLogger(Controller.class);
    private final TaskRepository taskRep;

    public Controller(TaskRepository taskRep)
    {
        this.taskRep = taskRep;
    }

    @GetMapping
    public List<Task> getAllTasks()
    {
        log.info("Request to get task list");
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
        msg.sendTaskNotification("A new task was created: " + saveTask.getTitle());
        return new ResponseEntity<>(saveTask, HttpStatus.CREATED);
    }

    @Cacheable(value = "tasks", key = "#id")
    @GetMapping("/{id}")
    public ResponseEntity<Task> getTaskById(@PathVariable Long id)
    {
        log.info("Finding a task with ID: {}", id);
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

    @CacheEvict(value = "tasks", key = "#id")
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteTask(@PathVariable Long id)
    {
        log.info("Request to delete a task with ID: {}", id);
        if (taskRep.existsById(id))
        {
            taskRep.deleteById(id);
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.notFound().build();
    }

}