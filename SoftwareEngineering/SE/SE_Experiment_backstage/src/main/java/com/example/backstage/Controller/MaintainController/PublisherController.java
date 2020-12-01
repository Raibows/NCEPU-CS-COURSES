package com.example.backstage.Controller.MaintainController;

import com.example.backstage.Entity.MaintainEntity.Publisher;
import com.example.backstage.Entity.MaintainEntity.User;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.MatainService.PublisherService;
import io.swagger.annotations.*;
import net.minidev.json.JSONObject;
import org.omg.CORBA.INTERNAL;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

@Api("出版社管理")
@CrossOrigin
@Controller
@RequestMapping("maintain")
public class PublisherController {
    @Autowired
    PublisherService publisherService;


    /**
     *
     * @param
     * @return
     */
    @RequestMapping(value = "/queryAllPublisher",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询出版社")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "publisher",value = "出版社信息",required = true),
    })
    public ResultVO findAll(@RequestBody JSONObject object){
         int page=Integer.parseInt(object.getAsString("page"));
         String name=object.getAsString("name");
         int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Publisher> list=publisherService.findAllByPage(name,pageable);
         if (list.getTotalElements()==0){
             return ResultVO.SUCCESS();
         }else {
             return ResultVO.SUCCESS(list);
         }
    }

    /**
     *
     * @param publisher
     * @return
     */
    @RequestMapping(value = "/queryPubIdAndName",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询出版社id和名字")
    @ApiImplicitParam(name = "publisher",value = "出版社信息",required = true,paramType = "Publisher")
    public ResultVO queryIdAndName(@RequestBody Publisher publisher){
          String name=publisher.getPublisherName();
          List<Publisher> list=publisherService.findAllIdName(name);
          if (list.size()==0){
              return ResultVO.SUCCESS();
          }else {
              return ResultVO.SUCCESS(list);
          }
    }


    /**
     *
     * @param publisher
     * @return
     */
    @RequestMapping(value = "/addPublisher",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加出版社")
    @ApiImplicitParam(name = "publisher",value = "出版社信息",required = true,paramType = "Publisher")
    public ResultVO addPublisher(@RequestBody Publisher publisher){
          String phoneNumber=publisher.getPhoneNumber();
          if (publisherService.findPublisherByPhone(phoneNumber)!=null){
              return ResultVO.FAIL("电话号码已存在!");
          }
          else {
              publisherService.addPublisher(publisher);
              return ResultVO.SUCCESS("添加成功!");
          }
    }

    /**
     *
     * @param publisher
     * @return
     */
    @RequestMapping(value = "/updatePublisher",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("更新出版社")
    @ApiParam(name = "publisher",value = "出版社信息")
    public ResultVO updatePublisher(@RequestBody Publisher publisher){
        try {
            publisherService.addPublisher(publisher);
            return ResultVO.SUCCESS("修改成功!");
        }catch (Exception e){
            return ResultVO.FAIL("修改失败");
        }
    }

    /**
     *
     * @param publisher
     * @return
     */
    @RequestMapping(value = "/deletePublisher",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("删除出版社")
    @ApiParam(name = "publisher",value = "出版社信息")
    public ResultVO deletePublisher(@RequestBody Publisher publisher){
        int id=publisher.getId();
        try {
            publisherService.deleteById(id);
            return ResultVO.SUCCESS("删除成功!");
        }catch (Exception e){
            return ResultVO.FAIL("删除失败");
        }
    }
}
