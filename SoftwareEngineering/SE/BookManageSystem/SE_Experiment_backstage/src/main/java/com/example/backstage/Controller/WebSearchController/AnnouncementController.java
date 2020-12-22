package com.example.backstage.Controller.WebSearchController;

import com.example.backstage.Entity.WebSearchEntity.Announcement;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.WebSearchService.AnnouncementService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.text.SimpleDateFormat;
import java.util.Date;

@Controller
@RequestMapping("/search")
@Api("公告管理")
@CrossOrigin
public class AnnouncementController {
    @Autowired
    private AnnouncementService service;

    /**
     *
     * @param object
     * @return
     */
    @RequestMapping(value = "/queryAllAnn",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询所有公告")
    @ApiParam(name = "Ann",value = "页数及每页大小",required = true)
    public ResultVO queryAllAnn(@RequestBody JSONObject object){
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Announcement> list=service.findAllByPage(pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }


    /**
     *
     * @param ann
     * @return
     */
    @RequestMapping(value = "/addAnn",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加公告")
    @ApiImplicitParam(name = "ann",value = "公告信息",required = true)
    public ResultVO addAnn(@RequestBody Announcement ann){
        Date publishDate=ann.getPublishDate();
        Date endDate=ann.getEndDate();
        int compare=publishDate.compareTo(endDate);
        if (compare==1){
            return ResultVO.SUCCESS("发布日期不能大于结束日期");
        }else {
            try {
                service.addAnnouncement(ann);
                return ResultVO.SUCCESS("添加成功!");
            } catch (Exception e) {
                return ResultVO.FAIL();
            }
        }
    }

    /**
     *
     * @param ann
     * @return
     */
    @RequestMapping(value = "/deleteAnn",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("删除公告")
    @ApiImplicitParam(name = "id",value = "公告id",required = true)
    public ResultVO deleteAnn(@RequestBody Announcement ann){
        int id=ann.getId();
        try {
            service.deleteAnnouncement(id);
            return ResultVO.SUCCESS("删除成功!");
        }catch (Exception e){
            return ResultVO.FAIL("删除失败!");
        }
    }

    @RequestMapping(value = "/updateAnn",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("更新公告")
    @ApiImplicitParam(name = "ann",value = "公告信息",required = true)
    public ResultVO updateAnn(@RequestBody Announcement ann){
        try {
            service.addAnnouncement(ann);
            return ResultVO.SUCCESS("更新成功!");
        }catch (Exception e){
            return ResultVO.FAIL("更新失败!");
        }
    }
}
