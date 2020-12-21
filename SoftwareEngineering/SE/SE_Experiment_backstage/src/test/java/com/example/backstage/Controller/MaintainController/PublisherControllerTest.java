package com.example.backstage.Controller.MaintainController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.MaintainEntity.Publisher;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

/** 
* PublisherController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class PublisherControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: findAll(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testFindAll() throws Exception { 
//TODO: Test goes here...
    String str="{\"name\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/maintain/queryAllPublisher")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: queryIdAndName(@RequestBody Publisher publisher) 
* 
*/ 
@Test
public void testQueryIdAndName() throws Exception { 
//TODO: Test goes here...
    Publisher publisher=new Publisher();
    publisher.setPublisherName("勋泽出版社");
    String json= JSONObject.toJSONString(publisher);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/queryPubIdAndName")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addPublisher(@RequestBody Publisher publisher) 
* 
*/ 
@Test
public void testAddPublisher() throws Exception { 
//TODO: Test goes here...
    Publisher publisher=new Publisher("宝贵出版社","华电路123号","18564789613");
    String json= JSONObject.toJSONString(publisher);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/addPublisher")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
}

/** 
* 
* Method: updatePublisher(@RequestBody Publisher publisher) 
* 
*/ 
@Test
public void testUpdatePublisher() throws Exception { 
//TODO: Test goes here...
    Publisher publisher=new Publisher("云贵出版社","华电路123号","18564789613");
    String json= JSONObject.toJSONString(publisher);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/updatePublisher")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deletePublisher(@RequestBody Publisher publisher) 
* 
*/ 
@Test
public void testDeletePublisher() throws Exception { 
//TODO: Test goes here...
    Publisher publisher=new Publisher("云贵出版社","华电路123号","18564789613");
    publisher.setId(8);
    String json= JSONObject.toJSONString(publisher);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/deletePublisher")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
