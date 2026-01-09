package com.rest.crud;

import io.qameta.allure.*;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.bean.override.mockito.MockitoBean;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest(properties = {
        "spring.autoconfigure.exclude=org.springframework.boot.autoconfigure.amqp.RabbitAutoConfiguration",
        "spring.rabbitmq.listener.auto-startup=false",
        "app.rabbitmq.queue=task-queue"
})
@AutoConfigureMockMvc
@Epic("REST API Tasks")
@Feature("CRUD Operations")
public class TestController
{

    @Autowired
    private MockMvc mockMvc;

    @MockitoBean
    private TaskRepository taskRep;

    @MockitoBean
    private Message msg;

    @Test
    @Description("Verify that a task can be successfully created and retrieved")
    public void createAndGetTaskTest() throws Exception
    {
        createTaskStep();
        getTasksStep();
    }

    @Step("Send POST request to create a new task")
    public void createTaskStep() throws Exception
    {
        String json = "{\"title\":\"Test Task\", \"description\":\"Description\", \"status\":\"todo\"}";

        org.mockito.Mockito.when(taskRep.save(org.mockito.Mockito.any(Task.class)))
                .thenReturn(new Task(1L, "Test Task", "Description", "todo"));

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isCreated());
    }

    @Step("Send GET request to retrieve all tasks")
    public void getTasksStep() throws Exception
    {
        mockMvc.perform(get("/tasks"))
                .andExpect(status().isOk());
    }
}